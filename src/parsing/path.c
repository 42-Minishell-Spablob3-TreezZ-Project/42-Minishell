/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:42:53 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/05 13:45:02 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*check_path(char **path_array, t_command *cmd)
{
	char	*dir_plus_bar;
	int		i;
	char	*result;
		
	i = 0;
	while (path_array[i])
	{
		dir_plus_bar = ft_strjoin(path_array[i], "/");
		result = ft_strjoin(dir_plus_bar, cmd->argv[0]);
		free(dir_plus_bar);
		if (access(result, X_OK) == 0)
		{
			free_array(path_array);
			return(result);
		}
		free(result);
		i++;
	}
	free_array(path_array);
	return (NULL);
}

char	*find_path(t_command *cmd, t_env **env)
{
	char	*result;
	t_env	*temp;
	char	**path_array;
	
	temp = *env;
	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (access(cmd->argv[0], X_OK) == 0) //verifica se o ficheiro existe e se e executavel -> (X_OK)
			return(result = ft_strdup(cmd->argv[0]));
		else
			return (NULL);
	}
	while (temp)
	{
		if (ft_strcmp(temp->key, "PATH") == 0)
		{
			path_array = ft_split(temp->value, ':');
			if (!path_array)
				return (NULL);
			return (check_path(path_array, cmd));
		}
		temp = temp->next;
	}
	return (NULL);
}
