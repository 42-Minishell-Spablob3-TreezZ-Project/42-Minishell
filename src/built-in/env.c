/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:26 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/19 12:38:55 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	env_bultin(t_env **env, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	int		key_len;
	char	*equal_sign;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (!equal_sign)
		{
			key = ft_strdup(envp[i]);
			value = NULL;
		}
		else
		{
			key_len = equal_sign - envp[i];
			key = ft_substr(envp[i], 0, key_len);
			value = ft_strdup(equal_sign + 1);
		}
		add_env_node(env, key, value);
		i++;
	}
	print_env_list(env);
}
void	add_env_node(t_env **env, char *key, char *value)
{
	t_env *env_node;

	env_node = malloc(sizeof(t_env));
	env_node->key = key;
	env_node->value = value;
	env_node->next = *env;
	*env = env_node;
}

void	print_env_list(t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}