/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:49:02 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/19 13:16:33 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_built_in(t_command *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		echo_builtin(cmd->argv);
		printf("echo executado\n");
		exit(0);
	}
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		get_current_dir();
		printf("pwd executado\n");
		exit(0);
	}
	return (1);
}

int	exec_parent_built_in(t_command *cmd, t_env **env)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		cd_builtin(cmd, env);
		return (0);
	}
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
	{
		print_env_list(env);
		return (0);
	}
	return (1);
}

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}