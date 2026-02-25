/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:26 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/24 15:07:08 by joapedro         ###   ########.fr       */
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
}
void	add_env_node(t_env **env, char *key, char *value)
{
	t_env	*env_node;
	t_env	*head;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return ;
	env_node->next = NULL;
	if (!(*env))
	{
		env_node->key = key;
		env_node->value = value;
		*env = env_node;
		return ;
	}
	env_node->key = key;
	env_node->value = value;
	head = *env;
	while (head->next)
		head = head->next;
	head->next = env_node;
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
int	env_array_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return(i);
}

char	**env_to_array(t_env *env)
{
	int		len;
	char	**env_array;
	int		i;
	char	*temp;

	len = env_array_len(env);
	env_array = malloc((len + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		if (env->value)
			env_array[i] = ft_strjoin(temp, env->value);
		else
			env_array[i] = ft_strdup(temp);
		free(temp);
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
