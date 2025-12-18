#include "../includes/minishell.h"

void	tokenize_operator(char *cmd, t_tokens *new, int *i)
{
	
}

int	which_token(char *cmd, int *i)
{
	if (cmd[*i] == 32 || (cmd[*i] >= 9 && cmd[*i] <= 13))
		(*i)++;
	else if (cmd[*i] == '|' || cmd[*i] == '>' || cmd[*i] == '<')
		return (0);
	return (*i);
}

//#include <stdio.h>

/* int	main(void) */
/* { */
/* 	char	*str = "hello > yo"; */
/* 	int	i = 0; */
/* 	while (str[i]) */
/* 		printf("%i\n", which_token(str, &i)); */
/* 	return (0); */
/* } */
