#include "includes/minishell.h"

void	handle_builtin(char *argv)
{
	(void)argv;
	while (1)
	{
		readline("Minisheila>$ ");
	}
}

int	main(int argc, char **argv)
{
	
	(void)argc;
	handle_builtin(argv[1]);
	return (0);
}

/* int	main(int argc, char **argv) */
/* { */
/* 	char	*test; */
	
/* 	test = readline(argv[1]); */
/* 	printf("%s", test); */
/* 	return (0); */
/* } */
