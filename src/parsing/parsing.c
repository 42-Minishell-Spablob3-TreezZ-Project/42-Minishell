#include "../includes/minishell.h"

//Mode for treating stuff with quotes, and without

/* check_token_word() */
/* { */
	
/* } */

/* wejh90df */

/* int	tokenize(char **split) */
/* { */
/* 	while (*split) */
/* 	{ */
		
/* 		split++; */
/* 	} */
/* 	return (1); */
/* } */

//Idea
/* token coiso(args) */
/* { */
/* 	int	i; */
/* 	int	j; */
/* 	char	**holder; */

/* 	while (args[i]) */
/* 	{ */
/* 		holder[j] = tokenizer_function(result[i]); */
/* 		i++; */
/* 		j++; */
/* 	} */
/* } */

char	*parse_command(char *cmd)
{
	int		i;
	char	**splits;
	char	**results;

	i = 0;
	splits = 
//	splits = ft_split(cmd, ' ');
	results = tokenize(splits[i]);
	while (results[i])
		i++;
	if (i == 1)
		return (results[0]);
	if (i > 1)
	{
		return ("FALTA ISTO");
	}
	return NULL;
}

int	class_command(char *cmd)
{
	char	*parsed;

	parsed = parse_command(cmd);
	if (!parsed)
		return (1);
	if (ft_strncmp (parsed, "exit", INT_MAX) == 0)
		return (0);
//If invalid command
	else if (parsed)
	{
		ft_printf("%s: command not found\n", parsed);
		return (1);
	}
	return (1);
}
