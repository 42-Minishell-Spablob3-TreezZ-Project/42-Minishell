/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:48:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/11 14:46:45 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	close_parent_fds(t_command *cmd, int pipe_fd[2], int *prev_fd)
{
	t_heredoc	*tmp;

	if (*prev_fd != -1)
		close(*prev_fd);
	tmp = cmd->heredocs;
	while (tmp)
	{
		close(tmp->fd[0]);
		tmp = tmp->next;
	}
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

static void	execve_func(t_command *cmd, char *path, t_env **env)
{
	char	**env_array;

	env_array = env_to_array(*env);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": command not found\n", 20);
		free_array(env_array);
		clear_env_list(env);
		free_command(cmd->head);
		exit(127);
	}
	execve(path, cmd->argv, env_array);
	if (errno == EACCES)
	{
		write(2, "Minishell: permission denied\n", 29);
		g_exit_status = 126;
		exit(126);
	}
	perror("minishell");
	free_array(env_array);
	clear_env_list(env);
	free_command(cmd->head);
	exit(127);
}

static void	child_process(t_command *cmd, int pipe_fd[2], \
int prev_fd, t_env **env)
{
	char	*path;

	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (cmd->heredocs)
		dup_heredoc(cmd);
	if (cmd->next)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (cmd->infile)
		execute_redir_in(cmd);
	if (cmd->outfile || cmd->append)
		execute_redir_out(cmd);
	if (execute_child_builtin(cmd, env))
		exit(0);
	path = find_path(cmd, env);
	execve_func(cmd, path, env);
}

static int	create_pipe(t_command *cmd, int pipe_fd[2])
{
	if (cmd->next)
	{
		if (pipe(pipe_fd) < 0)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

void	execute_command(t_command *cmd, t_env **env)
{
	int			pipe_fd[2];
	int			prev_fd;
	pid_t		pid;
	pid_t		last_pid;
	pid_t		wait_pid;
	int			status;

	prev_fd = -1;
	while (cmd)
	{
		init_heredoc(cmd);
		if (create_pipe(cmd, pipe_fd) < 0)
			return ;
		if (exec_parent_built_in(cmd, env) == 0)
			return ;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (cmd->next == NULL)
			last_pid = pid;
		if (pid == 0)
			child_process(cmd, pipe_fd, prev_fd, env);
		close_parent_fds(cmd, pipe_fd, &prev_fd);
		cmd = cmd->next;
	}
	while ((wait_pid = wait(&status)) > 0)
	{
		if (wait_pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
	}
}
