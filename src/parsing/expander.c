/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:50:06 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/26 16:53:00 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_tokens(t_tokens *tokens)
{
	char	*tmp;

	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			tmp = tokens->input;
			tokens->input = expand_word(tokens->input);
			free(tmp);
		}
		tokens = tokens->next;
	}
}

char	*expand_word(char *str)
{
	char	*result;

	result = NULL;
	while (*str)
	{
		if (*str == '\'')
			handle_single_quotes(&str, &result);
		else if (*str == '"')
			handle_double_quotes(&str, &result);
		else if (*str == '$')
			handle_dollar(&str, &result);
		else
		{
			result = ft_append(result, *str);
			str++;
		}
	}
	return (result);
}

char	*ft_append(char *dest, char c)
{
	int		len;
	char	*new;
	int		i;

	if (!dest)
		len = 0;
	else
		len = ft_strlen(dest);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	i = 0;
	if (dest)
	{
		while (dest[i])
		{
			new[i] = dest[i];
			i++;
		}
		free(dest);
	}
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
}

char	*expand_variable(char **str)
{
	char	*start;
	int		len;
	char	*var_name;
	char	*env_var;

	(*str)++;
	start = *str;
	if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(g_exit_status));
	}
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	len = *str - start;
	var_name = ft_substr(start, 0, len);
	env_var = getenv(var_name);
	free(var_name);
	if (!env_var)
		return (NULL);
	return (ft_strdup(env_var));
}
