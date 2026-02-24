/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:56:29 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/24 15:44:01 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Ponteiro para o previous node
void	add_token(t_tokens **tokens, t_tokens *new)
{
	t_tokens	*last;

	new->next = NULL;
	if (!(*tokens))
	{
		*tokens = new;
		new->prev = NULL;
		return ;
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	tokenization(t_tokens **tokens, char *cmd)
{
	int			i;
	t_tokens	*new;

	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && is_space(cmd[i]))
			i++;
		if (!cmd[i])
			break ;
		new = ft_calloc(1, sizeof(t_tokens));
		if (is_operator(cmd[i]))
			tokenize_operator(cmd, new, &i);
		else
			tokenize_word(cmd, new, &i);
		add_token(tokens, new);
	}
}

t_command	*start_lexer(char *cmd)
{
	t_command 	*command;
	t_tokens	*tokens;

	tokens = NULL;
	if (!cmd)
		return (NULL);
	tokenization(&tokens, cmd);
	expand_tokens(tokens);
	command = parse_cmd(tokens);
	free_tokens(tokens);
	return(command);
}

int	class_command(char *cmd, t_env **env)
{
	t_command	*command;

	command = start_lexer(cmd);
	if (!command)
		return (0);
	if (command->argv && ft_strncmp (command->argv[0], "exit", INT_MAX) == 0)
	{
		free(command);
		return (0);
	}
	execute_command(command, env); 
	free_command(command);
	return (1);
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
void	free_command(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd->heredoc_delimiter);
		free(cmd);
		cmd = tmp;
	}
}
