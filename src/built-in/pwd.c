/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:54:46 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/19 11:54:47 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void get_current_dir()
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
}