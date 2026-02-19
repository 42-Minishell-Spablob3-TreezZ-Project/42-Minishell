/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:56:24 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/19 11:56:26 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	else if (cmd[*i] == '>')
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

int	which_token(char *cmd, int *i)
{
	if (cmd[*i] == 32 || (cmd[*i] >= 9 && cmd[*i] <= 13))
		(*i)++;
	else if (cmd[*i] == '|' || cmd[*i] == '>' || cmd[*i] == '<')
		return (0);
	return (1);
}

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}
