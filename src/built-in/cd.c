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

int	cd_builtin(t_command *cmd)
{
	char	*path;
	int		i;
	
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (ft_strncmp(cmd->argv[i], "cd", INT_MAX) == 0 && !cmd->argv[i + 1])
			path = getenv("HOME");
		if (ft_strncmp(cmd->argv[i], "~", INT_MAX) == 0 && cmd->argv[i - 1])
			path = getenv("HOME");
		else
			path = cmd->argv[i];
		i++;
	}
	if (chdir(path) != 0)
	{
		printf ("cd: %s: No such file or directory\n", path);
		return (1);
	}
	printf("PRINT do path: %s\n", path);
	return (0);
}

//cd: def: No such file or directory