#include "../includes/minishell.h"

//Mode for treating stuff with quotes, and without

int	get_args(char *cmd)
{
	int	i;
	int	j;
	int	args;

	i = 0;
	args = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == 32)
			i++;
		if (cmd[i] > 32 && cmd[i] < 127)
		{
//			args++;
			if (cmd[i] == 34 || cmd[i] == 39)
			{
				j = i;
				j++;
				while (cmd[j] && (cmd[j] != 34 && cmd[j] != 39))
				{
					if (cmd[j + 1] == 34 || cmd[j + 1] == 39)
					{
						i = j;
						break ;
					}
					else
						j++;
				}
			}
//			else
//				i++;
//			args++;
		}
		i++;
		if (cmd[i] == 34 || cmd[i] == 39)
			i++;
		if (!cmd[i] || cmd[i] == 32)
			args++;
	}
	return (args);
}

char	**treat_command(char *cmd)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	array = get_args(cmd);
	while (cmd[i])
	{
		while (skip_spaces(cmd[i]))
			i++;
		while ()
		
		i++;
	}
}

char	*parse_command(char *cmd)
{
	int		i;
	char	**words;

	i = 0;
//	words = get_words(cmd);
	words = treat_command(cmd);
	while (words[i])
		i++;
	if (i == 1)
		return (words[0]);
	if (i > 1)
	{
		return (NULL);
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


//BACKUP FOR TOKENIZATION AFTERWARDS
/* char	*parse_command(char *cmd) */
/* { */
/* 	int		i; */
/* 	char	**splits; */
/* 	char	**results; */

/* 	i = 0; */
/* 	splits = treat_command(cmd); */
/* //	splits = ft_split(cmd, ' '); */
/* 	results = tokenize(splits[i]); */
/* 	while (results[i]) */
/* 		i++; */
/* 	if (i == 1) */
/* 		return (results[0]); */
/* 	if (i > 1) */
/* 	{ */
/* 		return ("FALTA ISTO"); */
/* 	} */
/* 	return NULL; */
/* } */
