/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:06 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/19 14:44:46 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_env_var(t_env **env, char *oldpwd, char *pwd)
{
	t_env	*temp;
	int		OLDPWD_VAR;
	temp = *env;
	
	OLDPWD_VAR = 0;
	while (temp)
	{
		if (ft_strcmp(temp->key, "PWD") == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(pwd);
		}
		else if (ft_strcmp(temp->key, "OLDPWD") == 0)
		{
			OLDPWD_VAR = 1;
			free(temp->value);
			temp->value = ft_strdup(oldpwd);
		}
		temp = temp->next;
	}
		if (!OLDPWD_VAR)
			add_env_node(env, "OLDPWD", ft_strdup(oldpwd));
}

static char	*get_path(t_command *cmd, t_env **env)
{
	char *path;

	if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "~") == 0)
	{
		path = (get_env("HOME", env));
		if (!path)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
		return (path);
	}
	if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		path = (get_env("OLDPWD", env));
		if (!path)
		{
			printf("cd: OLDPWD not set\n");
			return (NULL);
		}
		printf("%s\n", path);
		return (path);
	}
	return (cmd->argv[1]);
}

char	*get_env(char *str, t_env **env)
{
	t_env	*temp;

	temp = *env;
	while(temp)
	{
		if(ft_strcmp(str, temp->key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	cd_builtin(t_command *cmd, t_env **env)
{
	char	*path;
	char	*pwd;
	char	*curr_dir;

	pwd = getcwd(NULL, 0);
	path = get_path(cmd, env);
	if (!path )
	{
		free(pwd);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(pwd);
		return (1);
	}
	curr_dir = getcwd(NULL, 0);
	update_env_var(env, pwd, curr_dir);
	free(pwd);
	free(curr_dir);
	return (0);
}
