#include "includes/minishell.h"

int	main(void)
{
	handle_signals();
	start_shell();
	return (0);
}

/* int	main(int argc, char **argv) */
/* { */
/* 	char	*test; */
	
/* 	test = readline(argv[1]); */
/* 	printf("%s", test); */
/* 	return (0); */
/* } */
