/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:33:17 by grui-ant          #+#    #+#             */
/*   Updated: 2026/03/11 15:34:14 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cd_args(t_command *cmd)
{
	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	check_cd_path(char *path, char *oldpwd)
{
	if (!path)
	{
		free(oldpwd);
		free(path);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}
