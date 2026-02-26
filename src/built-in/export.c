/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:35 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/26 15:52:41 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	verify_env_var(char *var_key, char *value, t_env **env)
{
	t_env	*temp;
	
	if (!is_valid(var_key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(var_key, 2);
		ft_putstr_fd("=", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_exit_status = 1;
		return (0);
	}
	temp = *env;
	while (temp)
	{
		if (ft_strcmp(var_key, temp->key) == 0)
		{
			delete_node(env, var_key);
			g_exit_status = 0;
			return (1);
		}
		temp = temp->next;
	}
	g_exit_status = 0;
	return (1);
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
		if (!equal_sign)
		{
			return ;
			g_exit_status = 1;
		}
		key_len = equal_sign - cmd->argv[i];
		key = ft_substr(cmd->argv[i], 0, key_len);
		value = ft_strdup(equal_sign + 1);
		if(!verify_env_var(key, value, env))
		{
			free(key);
			free(value);
			i++;
			continue;
		}
		add_env_node(env, key, value);
		i++;
	}
}
