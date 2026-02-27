/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:56:57 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/25 14:02:36 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*create_prompt(void)
{
	char	*prompt;

	prompt = "@minisheila>$ ";
	prompt = ft_strjoin(getenv("USER"), prompt);
	return (prompt);
}

void	start_shell(char **envp)
{
	char	*command;
	char	*prompt;
	t_env	*env;

	command = NULL;
	prompt = create_prompt();
	env = NULL;
	env_bultin(&env, envp);
	while (1)
	{
		command = readline(prompt);
		if (!class_command(command, &env))
		{
			free (command);
			printf("exit\n");
			break ;
		}
		add_history(command);
		free (command);
	}
	clear_env_list(&env);
	rl_clear_history();
	free (prompt);
}
