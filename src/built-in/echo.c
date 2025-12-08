#include "../includes/minishell.h"

int	check_n_flag(char *argv)
{
	int	i;

	i = 0;
	if (argv[0] == '-' && argv[1] == 'n')
		return (1);
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}


void	echo_builtin(char **argv)
{
	int i;
	int newline;

	i = 1;
	newline = 0;

	while (argv[i] && check_n_flag(argv[i]))
	{
		newline = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
	}
	if (newline)
		printf("\n");
}