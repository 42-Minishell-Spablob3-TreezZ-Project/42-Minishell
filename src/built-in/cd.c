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

int	cd_builtin(t_command *cmd, char **envp)
{
	char	*path;
	//char	*oldpwd;
	//char	*pwd;

	//pwd = getcwd(NULL, 0);
	if (!cmd->argv[1] || ft_strncmp(cmd->argv[1], "~", INT_MAX) == 0)
		path = getenv("HOME");
	else if (ft_strncmp(cmd->argv[1], "-", INT_MAX) == 0)
		path = getenv("OLDPWD");
	else
		path = cmd->argv[1];

	if (chdir(path) != 0)
	{
		printf ("cd: %s: No such file or directory\n", path);
		return (1);
	}
	update_env_var(envp, path);
	printf("PRINT do path: %s\n", path);
	return (0);
}

char	*update_env_var(char **envp, char *path)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			free(envp[i]);
			envp[i] = ft_strjoin("PWD=", path);
		}
		i++;
	}
	return (envp[i]);
}


//Implementar "cd -" -> vai para diretorio anterior.
//Sempre que cd funciona, PWD tem de ser atualizado e o OLDPWD -> diretorio anterior
//ERRO cd: def: No such file or directory
