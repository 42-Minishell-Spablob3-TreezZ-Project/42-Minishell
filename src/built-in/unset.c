/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:48:28 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/24 15:36:42 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	delete_node(t_env **head, char *key)
{
	t_env	*temp;
	t_env	*current;

	current = *head;
	if (ft_strcmp((*head)->key, key) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->value);
		free(temp->key);
		free(temp);
		return ;
	}
	while (current)
	{
		if (ft_strcmp(current->next->key, key)== 0)
		{
			temp = current;
			free(temp->next->value);
			free(temp->next->key);
			free(temp->next);
			current->next = current->next->next;
			return ;
		}
		current = current->next;
	}
}

void	unset_built_in(t_command *cmd, t_env **env)
{
	t_env	*temp;
	int	i;

	temp = *env;
	i = 1;
	while (temp && cmd->argv[i])
	{
		if (*cmd->argv && ft_strcmp(cmd->argv[i], temp->key) == 0)
		{
			delete_node(env, temp->key);
			i++;
		}
		else if (!*cmd->argv)
			return ;
		temp = temp->next;
	}
}
