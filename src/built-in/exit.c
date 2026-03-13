/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:32 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/11 12:38:20 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_digit(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' || av[i][j] == '+')
				j++;
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
			else
				j++;
		}
		i++;
	}
	return (1);
}

static	void	too_many_arguments(void)
{
	ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
	g_exit_status = 1;
}

void	exit_builtin(t_command *cmd, t_env **env)
{
	if (!cmd->argv[1])
	{
		printf("exit\n");
		clear_env_list(env);
		free_command(cmd);
		exit(g_exit_status);
	}
	else if (cmd->argv[2])
		too_many_arguments();
	else if (cmd->argv[0] && cmd->argv[1])
	{
		if (!is_digit(&cmd->argv[1]))
		{
			ft_putstr_fd("Minishell: numeric argument required\n", 2);
			clear_env_list(env);
			free_command(cmd);
			exit(2);
		}
		g_exit_status = ft_atoi(cmd->argv[1]) % 256;
		printf("exit\n");
		clear_env_list(env);
		free_command(cmd);
		exit((unsigned char)g_exit_status);
	}
}
