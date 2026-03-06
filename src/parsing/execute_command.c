/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:48:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/06 11:15:17 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void	close_parent_fds(t_command *cmd, int pipe_fd[2], int *prev_fd)
{
	t_heredoc *tmp;
	
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
		close(pipe_fd[1]);//fechar o write
		*prev_fd = pipe_fd[0]; //read para o proximo comando
	}
}

static void	execve_function(char *path, t_command *cmd, t_env **env)
{
	char	**env_array;
	
	env_array = env_to_array(*env);
	if (path)
		execve(path, cmd->argv, env_array);
	free(path);
	perror("execve failed");
	g_exit_status = 127;
	free_array(env_array); //dar free na env_array; (por no exit function)
	clear_env_list(env);
	free_command(cmd);
	exit(1);
}

static void	child_process(t_command *cmd, int pipe_fd[2], int prev_fd, t_env **env)
{
	char	*path;
	
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0); //redireciona STDIN para o pipe.
		close(prev_fd); // fechar o fd do comando anterior original.
	}
	if (cmd->heredocs)
		dup_heredoc(cmd);
	if (cmd->next)
	{
		dup2(pipe_fd[1], 1); //redireciona STDOUT para novo pipe.
		close(pipe_fd[0]); // fecha o pipe 
		close(pipe_fd[1]);
	}
	if (cmd->outfile || cmd->append)
		execute_redir_out(cmd);
	if (cmd->infile)
		execute_redir_in(cmd);
	if (execute_built_in(cmd, env))
		exit(0);
	path = find_path(cmd, env);
	execve_function(path, cmd, env);
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

void execute_command(t_command *cmd, t_env **env)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

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
		if (pid == 0)
			child_process(cmd, pipe_fd, prev_fd, env);
		close_parent_fds(cmd, pipe_fd, &prev_fd);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);
}
