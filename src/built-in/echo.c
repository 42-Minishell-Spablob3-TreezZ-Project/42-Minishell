/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:10 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/23 15:19:06 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int	check_n_flag(char *argv)
{
	int	i;

	i = 0;
	if (!argv || argv[0] != '-' || argv[1] != 'n')
		return (0);
	i = 1;
	while (argv[i] == 'n')
		i++;
	if (!argv[i])
		return (1);
	if (argv[i] != 'n')
		return (0);
	else
		return(1);
}

void	echo_builtin(char **argv)
{
	int i;
	int n_flag;

	i = 1;
	n_flag = 0;

	if (argv[i] && check_n_flag(argv[i]))
		n_flag = 1;
//	i = 2; Talvez adicionar este i = 2 ao if de cima e tirar n_flag
	while (argv[i])
	{
		if (!argv[i + 1])
			printf("%s", argv[i]);
		else
			printf("%s ", argv[i]);
		i++;
	}
	if (!n_flag)
		printf("\n");
}
