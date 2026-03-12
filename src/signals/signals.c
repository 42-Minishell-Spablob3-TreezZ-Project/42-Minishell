/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:56:48 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/12 15:27:37 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	block_signal(void)
{
	struct sigaction	s_sa;

	s_sa.sa_handler = SIG_DFL;
	s_sa.sa_flags = 0;
	sigemptyset(&s_sa.sa_mask);
	sigaction(SIGINT, &s_sa, NULL);
	sigaction(SIGQUIT, &s_sa, NULL);
}
	
void	sighandler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		if (g_exit_status == -1)
			g_exit_status = 130;
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_exit_status = 130;
		}
	}
}

void	sighandler_quit(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		g_exit_status = 131;
	}
}

int	handle_signals(void)
{
	struct sigaction	s_sa;

	s_sa.sa_sigaction = sighandler;
	s_sa.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sa.sa_mask);
	sigaction(SIGINT, &s_sa, NULL);

	s_sa.sa_handler = sighandler_quit;
	s_sa.sa_flags = 0;
	sigaction(SIGQUIT, &s_sa, NULL);
	return (0);
}
