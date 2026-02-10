#include "../includes/minishell.h"

void	sighandler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		g_sigint = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	handle_signals(void)
{
	struct sigaction	s_sa;

	s_sa.sa_sigaction = sighandler;
	s_sa.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sa.sa_mask);
	sigaction(SIGINT, &s_sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
