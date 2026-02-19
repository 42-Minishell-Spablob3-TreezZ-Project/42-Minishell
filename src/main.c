/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:56:40 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/19 11:56:42 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	handle_signals();
	start_shell(envp);
	exit(0);
}
