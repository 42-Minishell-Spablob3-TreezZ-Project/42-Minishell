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

static void	delete_first_node(t_env **head)
{
	t_env	*temp;
	
	if (!head || !*head)
		return ;
	temp = *head;
	*head = (*head)->next;
	free(temp->value);
	free(temp->key);
	free(temp);
	return ;
}

static void	delete_node(t_env **head, char *key)
{
	t_env	*temp;
	t_env	*current;

	if (ft_strcmp((*head)->key, key) == 0)
	{
		delete_first_node(head);
		return ;
	}
	current = *head;
	while (current && current->next)
	{
		if (ft_strcmp(current->next->key, key)== 0)
		{
			temp = current->next;
			current->next = temp->next;
			free(temp->value);
			free(temp->key);
			free(temp);
			return ;
		}
		current = current->next;
	}
}

void	unset_built_in(t_command *cmd, t_env **env)
{
	t_env	*temp;
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		temp = *env;
		while (temp)
		{
			if (ft_strcmp(cmd->argv[i], temp->key) == 0)
			{
				delete_node(env, temp->key);
				break ;
			}
			temp = temp->next;
		}
		i++;
	}
}
