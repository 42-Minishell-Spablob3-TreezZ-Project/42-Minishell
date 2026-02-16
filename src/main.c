#include "includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	handle_signals();
	start_shell(envp);
	exit(0);
}
