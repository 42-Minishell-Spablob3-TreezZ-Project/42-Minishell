/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:48:28 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/24 11:40:56 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_built_in(t_command *cmd, t_env **env)
{
	t_env	*temp;
	temp = *env;

	(cmd->argv)++;
	while (temp && cmd->argv)
	{
		if (cmd->argv == NULL)
			return ;
		else if (ft_strcmp(*cmd->argv, temp->key) == 0)
		{
			free(temp->key);
			if (temp->value)
				free(temp->value);
			free(temp);
			(cmd->argv)++;
		}
		temp = temp->next;
	}
}
