/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:48:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/12 15:35:39 by joapedro         ###   ########.fr       */
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_array(env_array);
		clear_env_list(env);
		free_command(cmd->head);
		exit(127);
	}
	execve(path, cmd->argv, env_array);
	if (errno == EACCES)
	{
		ft_putstr_fd("Minishell: Permission denied\n", 2);
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
	
	block_signal();
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

void	execute_command(t_command *cmd, t_env **env)
{
	int			pipe_fd[2];
	int			prev_fd;
	pid_t		pid;
	pid_t		last_pid;

	prev_fd = -1;
	while (cmd)
	{
		init_heredoc(cmd);
		if (pipe_or_built_in(cmd, pipe_fd, env))
			return ;
		g_exit_status = -1;
		pid = fork();
		if (neg_pid(pid))
			return ;
		if (cmd->next == NULL)
			last_pid = pid;
		if (pid == 0)
			child_process(cmd, pipe_fd, prev_fd, env);
		close_parent_fds(cmd, pipe_fd, &prev_fd);
		cmd = cmd->next;
	}
	wait_pid(last_pid);
}
