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
