/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:54:16 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/11 13:01:22 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_single_quotes(char **str, char **result)
{
	(*str)++;
	while (**str && **str != '\'')
	{
		*result = ft_append(*result, **str);
		(*str)++;
	}
	if (**str != '\'')
	{
		printf("Error: unclosed quotes detected.\033[0m\n");
		return ;
	}
	if (**str == '\'')
		(*str)++;
}

void	handle_double_quotes(char **str, char **result, t_env **env)
{
	(*str)++;
	while (**str && **str != '"')
	{
		if (**str == '$')
			handle_dollar(str, result, env);
		else
		{
			*result = ft_append(*result, **str);
			(*str)++;
		}
	}
	if (**str != '"')
	{
		printf("Error: unclosed quotes detected.\033[0m\n");
		return ;
	}
	if (**str == '"')
		(*str)++;
}

void	handle_dollar(char **str, char **result, t_env **env)
{
	char	*expanded;

	expanded = expand_variable(str, env);
	if (expanded)
	{
		if (!result)
			return ;
		*result = ft_strjoin(*result, expanded);
		free(expanded);
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
