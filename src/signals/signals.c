#include "../includes/minishell.h"

void	sighandler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
}

int	handle_signals(void)
{
	struct sigaction	s_sa;

	s_sa.sa_sigaction = sighandler;
	if (sigaction(SIGINT, &s_sa, NULL))
		return (1);
	return (0);
}
