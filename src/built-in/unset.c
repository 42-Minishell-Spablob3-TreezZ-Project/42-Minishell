/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:48:28 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/26 17:14:54 by grui-ant         ###   ########.fr       */
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

void	delete_node(t_env **head, char *key)
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
		if (ft_strcmp(current->next->key, key) == 0)
		{
			temp = current->next;
			current->next = temp->next;
			if (current->next)
			{
				free(temp->value);
				free(temp->key);
				free(temp);
			}
			return ;
		}
		current = current->next;
	}
}

int	is_valid(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset_built_in(t_command *cmd, t_env **env)
{
	t_env	*temp;
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!is_valid(cmd->argv[i]))
		{
			i++;
			continue ;
		}
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
