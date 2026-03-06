/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:49:02 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/06 10:59:41 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_built_in(t_command *cmd, t_env **env)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		echo_builtin(cmd->argv);
		free_command(cmd);
		clear_env_list(env);
		return (1);
	}
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		get_current_dir();
		free_command(cmd);
		clear_env_list(env);
		return (1);
	}
	return (0);
}

int	exec_parent_built_in(t_command *cmd, t_env **env)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		cd_builtin(cmd, env);
		return (0);
	}
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
	{
		export_built_in(cmd, env);
		return (0);
	}
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
	{
		unset_built_in(cmd, env);
		return (0);
	}
	return (1);
}


void	execute_redir_out(t_command *cmd)
{
	int	fd;

	if (cmd->outfile && cmd->append == 0)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, 1);
	close(fd);
}

void	execute_redir_in(t_command *cmd)
{
	int	fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror("open: infile");
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
}
