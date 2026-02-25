/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:52:09 by grui-ant          #+#    #+#             */
/*   Updated: 2026/02/25 14:02:31 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	clear_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

/* void	clear_env_list(t_env **env) */
/* { */
/* 	t_env	*tmp; */

/* 	tmp = *env; */
/* 	while (tmp) */
/* 	{ */
/* 		free(tmp->key); */
/* 		free(tmp->value); */
/* 		free(tmp); */
/* 		tmp = tmp->next; */
/* 	} */
/* } */
