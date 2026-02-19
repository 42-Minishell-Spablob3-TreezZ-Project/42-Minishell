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
	if (ft_strncmp(cmd->argv[0], "echo", INT_MAX) == 0)
	{
		echo_builtin(cmd->argv);
		printf("echo executado\n");
		exit(0);
	}
	if (ft_strncmp(cmd->argv[0], "pwd", INT_MAX) == 0)
	{
		get_current_dir();
		printf("pwd executado\n");
		exit(0);
	}
	return (1);
}