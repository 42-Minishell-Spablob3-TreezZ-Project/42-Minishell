/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:35 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/19 11:55:36 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	verify_env_var(char *cmd, t_env **env)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(cmd, temp->next->key) == 0)
		{
			free(temp->next->key);
			if (temp->value)
				free(temp->next->value);
		}	
		temp = temp->next->next;
	}
}
void	export_built_in(t_command *cmd, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	int		key_len;
	char	*equal_sign;
	
	i = 1;
	while (cmd->argv[i])
	{
		equal_sign = ft_strchr(cmd->argv[i], '=');
		key_len = equal_sign - cmd->argv[i];
		key = ft_substr(cmd->argv[i], 0, key_len);
		verify_env_var(key, env);
		value = ft_strdup(equal_sign + 1);
		add_env_node(env, key, value);
		i++;
	}
}
