/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:56:29 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/26 17:27:55 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	t_command	*command;
	t_tokens	*tokens;

	tokens = NULL;
	if (!cmd)
		return (NULL);
	tokenization(&tokens, cmd);
	expand_tokens(tokens);
	command = parse_cmd(tokens);
	free_tokens(tokens);
	return (command);
}

int	class_command(char *cmd, t_env **env)
{
	t_command	*command;

	if (!cmd)
		return (0);
	if (!cmd[0] || empty_prompt(cmd))
		return (1);
	command = start_lexer(cmd);
	if (!command)
		return (0);
	if (command->argv && ft_strncmp (command->argv[0], "exit", INT_MAX) == 0)
	{
		free_command(command);
		return (0);
	}
	execute_command(command, env);
	free_command(command);
	return (1);
}
