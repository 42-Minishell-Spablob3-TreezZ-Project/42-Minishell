#include "../includes/minishell.h"

int	check_n_flag(char *argv)
{
	int	i;

	i = 0;
	if (!argv || argv[0] != '-' || argv[1] != 'n')
		return (0);
	i = 1;
	while (argv[i] == 'n')
		i++;
	if (!argv[i])
		return (1);
	if (argv[i] != 'n')
		return (0);
	else
		return(1);
}


void	echo_builtin(char **argv)
{
	int i;
	int n_flag;

	i = 0;
	n_flag = 0;

	if (argv[i] && check_n_flag(argv[i]))
		n_flag = 1;
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
	}
	if (!n_flag)
		printf("\n");
}


/* 
TESTAGEM SEM INPUT VERDADEIRO!
int main(void)
{
	char *str[] = {"-n", NULL};
	echo_builtin(str);
} */