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

int	cd_builtin(t_command *cmd, t_env **env)
{
	char	*path;
	char	*pwd;
	char	*curr_dir;

	pwd = getcwd(NULL, 0);
	if (!cmd->argv[1] || ft_strncmp(cmd->argv[1], "~", INT_MAX) == 0)
		path = getenv("HOME");
	else if (ft_strncmp(cmd->argv[1], "-", INT_MAX) == 0)
	{
		path = get_env("OLDPWD", env);
		printf("%s\n", path);
	}
	else
		path = cmd->argv[1];
	if (chdir(path) != 0)
	{
		printf ("cd: %s: No such file or directory\n", path);
		return (1);
	}
	curr_dir = getcwd(NULL, 0);
	update_env_var(env, pwd, curr_dir);
	return (0);
}

void	update_env_var(t_env **env, char *oldpwd, char *pwd)
{
	t_env	*temp;
	int		OLDPWD_VAR;
	temp = *env;

	OLDPWD_VAR = 0;
	while (temp)
	{
		if (ft_strncmp(temp->key, "PWD", 3) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(pwd);
		}
		else if (ft_strncmp(temp->key, "OLDPWD", 6) == 0)
		{
			OLDPWD_VAR = 1;
			free(temp->value);
			temp->value = ft_strdup(oldpwd);
		}
		temp = temp->next;
	}
		if (!OLDPWD_VAR)
			add_env_node(env, "OLDPWD", oldpwd); //adicionar node OLDPWD à env list.
}

char	*get_env(char *str, t_env **env)
{
	t_env	*temp;
	char	*path;

	temp = *env;
	while(temp)
	{
		if(ft_strncmp(str, temp->key, INT_MAX) == 0)
			path = temp->value;
		temp = temp->next;
	}
	return (path);
}

//Implementar "cd -" -> vai para diretorio anterior.
//Sempre que cd funciona, PWD tem de ser atualizado e o OLDPWD -> diretorio anterior
//ERRO cd: def: No such file or directory
