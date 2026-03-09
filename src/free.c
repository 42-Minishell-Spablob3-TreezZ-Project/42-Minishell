/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:52:09 by grui-ant          #+#    #+#             */
/*   Updated: 2026/03/09 14:54:22 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	clear_env_list(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{	
		tmp = *env;
		*env = (*env)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	free_heredocs(t_heredoc *heredoc)
{
	t_heredoc	*tmp;
	t_heredoc	*next;
	
	tmp = heredoc;
	while(tmp)
	{
		next = tmp->next;
		free(tmp->delimiter);
		free(tmp);
		tmp = next;
	}
}

void	free_command(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
			free_array(cmd->argv);
		free(cmd->infile);
		free(cmd->outfile);
		free_heredocs(cmd->heredocs);
		free(cmd);
		cmd = tmp;
	}
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->input);
		free(tokens);
		tokens = tmp;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
