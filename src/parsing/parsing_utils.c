/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:56:24 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/11 16:57:27 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_redir_in(char *cmd, t_tokens *new, int *i)
{
	if (cmd[*i + 1] == '<')
	{
		new->type = TOKEN_HEREDOC;
		(*i) += 2;
	}
	else
	{
		new->type = TOKEN_REDIRIN;
		(*i)++;
	}
}

static void	check_redir_out(char *cmd, t_tokens *new, int *i)
{
	if (cmd[*i + 1] == '>')
	{
		new->type = TOKEN_APPEND;
		(*i) += 2;
	}
	else
	{
		new->type = TOKEN_REDIROUT;
		(*i)++;
	}
}

void	tokenize_operator(char *cmd, t_tokens *new, int *i)
{
	int	start;

	start = *i;
	if (cmd[*i] == '|')
	{
		new->type = TOKEN_PIPE;
		(*i)++;
	}
	else if (cmd[*i] == '<')
		check_redir_in(cmd, new, i);
	else if (cmd[*i] == '>')
		check_redir_out(cmd, new, i);
	new->input = ft_substr(cmd, start, *i - start);
}

t_tokens	*tokenize_word(char *cmd, t_tokens *new, int *i)
{
	int	start;

	start = *i;
	new->type = TOKEN_WORD;
	while (cmd[*i] && !is_space(cmd[*i]) && !is_operator(cmd[*i]))
		check_quotes(cmd, i);
	new->input = ft_substr(cmd, start, *i - start);
	return (new);
}

void	check_quotes(char *cmd, int *i)
{
	char	quote;

	if (is_quote(cmd[*i]))
	{
		quote = cmd[*i];
		(*i)++;
		while (cmd[*i] && cmd[*i] != quote)
			(*i)++;
		if (cmd[*i] && cmd[*i] == quote)
			(*i)++;
	}
	else
	{
		while (cmd[*i] && !is_space(cmd[*i]) && !is_operator(cmd[*i]))
			(*i)++;
	}
}
