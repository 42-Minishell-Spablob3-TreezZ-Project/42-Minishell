#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	handle_builtin(char *argv)
{
	readline("Spablob3's shell >$ ");
}

int	main(int argc, char **argv)
{
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
