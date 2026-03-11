/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_misc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:36:51 by grui-ant          #+#    #+#             */
/*   Updated: 2026/03/11 16:57:19 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	empty_prompt(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == ' ')
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i] && cmd[i] != ' ')
			return (0);
		return (1);
	}
	return (0);
}

int	which_token(char *cmd, int *i)
{
	if (cmd[*i] == 32 || (cmd[*i] >= 9 && cmd[*i] <= 13))
		(*i)++;
	else if (cmd[*i] == '|' || cmd[*i] == '>' || cmd[*i] == '<')
		return (0);
	return (1);
}
