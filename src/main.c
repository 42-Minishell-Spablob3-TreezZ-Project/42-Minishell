#include "includes/minishell.h"

void	handle_builtin(char *argv)
{
	char	*user;
	char	*host;
	char	*prompt;

	(void)argv;
	user = ft_strjoin(getenv("USER"), "@");
	host = "Minisheila";
	prompt = ft_strjoin(ft_strjoin(user, host), ">$ ");
	while (1)
	{
		readline(prompt);
	}
}

int	main(int argc, char **argv)
{
	
	(void)argc;
	(void)argv;
//	handle_builtin(argv[1]);
	hist_test();
	return (0);
}

/* int	main(int argc, char **argv) */
/* { */
/* 	char	*test; */
	
/* 	test = readline(argv[1]); */
/* 	printf("%s", test); */
/* 	return (0); */
/* } */
