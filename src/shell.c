/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:56:57 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/13 12:14:29 by joapedro         ###   ########.fr       */
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
	char	*line;
	char	*prompt;
	t_env	*env;

	line = NULL;
	env = NULL;
	env_bultin(&env, envp);
	while (1)
	{
		prompt = create_prompt();
		line = readline(prompt);
		free(prompt);
		if (!class_command(line, &env))
		{
			free (line);
			printf("exit\n");
			break ;
		}
		add_history(line);
		free (line);
	}
	clear_env_list(&env);
	rl_clear_history();
}
