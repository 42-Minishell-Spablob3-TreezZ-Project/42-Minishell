#include "includes/minishell.h"

int	main(void)
{
	handle_signals();
	start_shell();
	exit(0);
}
