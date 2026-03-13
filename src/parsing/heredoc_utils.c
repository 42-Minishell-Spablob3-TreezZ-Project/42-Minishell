/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 18:57:44 by jpmesquita        #+#    #+#             */
/*   Updated: 2026/03/13 12:31:07 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*expand_heredoc(char **str, t_env **env)
{
	char	*start;
	int		len;
	char	*var_name;
	char	*env_var;

	(*str)++;
	start = *str;
	if (**str == '$')
		return (ft_itoa(getpid()));
	if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(g_exit_status));
	}
	if (!**str || !(ft_isalpha(**str) || **str == '_'))
		return (ft_strdup("$"));
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	len = *str - start;
	var_name = ft_substr(start, 0, len);
	env_var = get_env(var_name, env);
	free(var_name);
	if (!env_var)
		return (ft_strdup(""));
	return (ft_strdup(env_var));
}

static	void	expand_line2(char **ptr, char **result, t_env **env)
{
	char	*tmp;
	int		i;

	tmp = expand_heredoc(ptr, env);
	i = 0;
	while (tmp[i])
	{
		*result = ft_append(*result, tmp[i]);
		i++;
	}
	free (tmp);
}

char	*expand_line(char *line, t_env **env)
{
	char	*result;
	char	*ptr;

	result = NULL;
	ptr = line;
	while (*ptr)
	{
		if (*ptr == '$')
			expand_line2(&ptr, &result, env);
		else
		{
			result = ft_append(result, *ptr);
			ptr++;
		}
	}
	free (line);
	return (result);
}
