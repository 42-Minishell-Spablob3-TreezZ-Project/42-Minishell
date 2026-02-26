/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:06 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/26 17:11:27 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_env_var(t_env **env, char *oldpwd, char *curr_dir)
{
	t_env	*temp;
	int		oldpwdvar;

	temp = *env;
	oldpwdvar = 0;
	while (temp)
	{
		if (ft_strcmp(temp->key, "PWD") == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(curr_dir);
		}
		else if (ft_strcmp(temp->key, "OLDPWD") == 0)
		{
			oldpwdvar = 1;
			free(temp->value);
			temp->value = ft_strdup(oldpwd);
		}
		temp = temp->next;
	}
	if (!oldpwdvar)
		add_env_node(env, "OLDPWD", ft_strdup(oldpwd));
}

static char	*get_path(t_command *cmd, t_env **env)
{
	char	*path;

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
	while (temp)
	{
		if (ft_strcmp(str, temp->key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	cd_builtin(t_command *cmd, t_env **env)
{
	char	*path;
	char	*oldpwd;
	char	*curr_dir;

	oldpwd = getcwd(NULL, 0);
	path = get_path(cmd, env);
	if (!path)
	{
		free(oldpwd);
		g_exit_status = 1;
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		g_exit_status = 1;
		return (1);
	}
	curr_dir = getcwd(NULL, 0);
	update_env_var(env, oldpwd, curr_dir);
	free(oldpwd);
	free(curr_dir);
	g_exit_status = 0;
	return (0);
}
