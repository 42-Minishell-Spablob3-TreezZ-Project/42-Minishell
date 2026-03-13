/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:24:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/11 13:26:11 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_redir(t_tokens *tmp)
{
	if (tmp->type == TOKEN_REDIROUT
		|| tmp->type == TOKEN_APPEND
		|| tmp->type == TOKEN_REDIRIN
		|| tmp->type == TOKEN_HEREDOC)
	{
		if (!tmp->next || tmp->next->type != TOKEN_WORD)
			return (1);
	}
	return (0);
}

int	validate_syntax(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			if (!tmp->next || !tmp->prev || tmp->next->type != TOKEN_WORD)
			{
				printf("minishell: syntax error near unexpected token `|`\n");
				return (0);
			}
		}
		else if (is_redir(tmp))
		{
			printf("minishell: syntax error near unexpected token `newline`\n");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
