/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils_misc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:24:54 by grui-ant          #+#    #+#             */
/*   Updated: 2026/03/12 13:05:03 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	neg_pid(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	return (0);
}

void	wait_pid(pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
}

int	create_pipe(t_command *cmd, int pipe_fd[2])
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

int	pipe_or_built_in(t_command *cmd, int *pipe_fd, t_env **env)
{
	if (create_pipe(cmd, pipe_fd) < 0)
		return (1);
	if (exec_parent_built_in(cmd, env) == 0)
		return (1);
	return (0);
}
