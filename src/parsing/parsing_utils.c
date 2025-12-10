#include "../includes/minishell.h"

char	*fakedup(const char *s, char c)
{
	char	*string;
	size_t	counter;

	counter = 0;
	while (s[counter] != '\0' && s[counter] != c)
	{
		counter++;
	}
	string = ft_calloc((counter + 1), sizeof(char));
	if (string == NULL)
	{
		return (NULL);
	}
	counter = 0;
	while (s[counter] != '\0' && s[counter] != c)
	{
		string[counter] = s[counter];
		counter++;
	}
	string[counter] = '\0';
	return (string);
}

char	**free_memory(char **array, int n)
{
	int	counter;

	counter = 0;
	while (counter < n)
	{
		free(array[counter]);
		counter++;
	}
	free(array);
	return (NULL);
}

char	**write_words(char **array, const char *cmd)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (words < get_args(cmd))
	{
		while (cmd[i] && cmd[i] == 32)
			i++;
		if (cmd[i] > 32 && cmd[i] < 127)
		{
			array[words] = fakedup(&cmd[i], limiter);
			if (!array[words])
				return (free_memory(array, words));
		}
		while (cmd[i] != limiter && cmd[i] != '\0')
			i++;
		words++;
	}
	array[words] = NULL;
	return (array);
}

int	search_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != 34 && str[i] != 39))
		i++;
	while (str[i])
	{
		if (str[i] == 34)
		{
			while 
		}
	}
}

char	*check_quote(char *str, char a, char b)
{
	int	i;

	i = 0;
	while (str[i] != a)
	{
		if (str[i] == b)
		{
			str = check_quote(str, b, a);
			break ;
		}
		i++;
	}
	return (&str[i]);
}

/* int	skip_spaces(char c) */
/* { */
/* 	return (c == 32 || (c >= 9 && c <= 13)); */
/* } */

/* #include <stdio.h> */

/* int	get_args(char *cmd) */
/* { */
/* 	int	i; */
/* 	int	j; */
/* 	int	args; */

/* 	i = 0; */
/* 	args = 0; */
/* 	while (cmd[i]) */
/* 	{ */
/* 		while (cmd[i] && cmd[i] == 32) */
/* 			i++; */
/* 		if (cmd[i] > 32 && cmd[i] < 127) */
/* 		{ */
/* //			args++; */
/* 			if (cmd[i] == 34 || cmd[i] == 39) */
/* 			{ */
/* 				j = i; */
/* 				j++; */
/* 				while (cmd[j] && (cmd[j] != 34 && cmd[j] != 39)) */
/* 				{ */
/* 					if (cmd[j + 1] == 34 || cmd[j + 1] == 39) */
/* 					{ */
/* 						i = j; */
/* 						break ; */
/* 					} */
/* 					else */
/* 						j++; */
/* 				} */
/* 			} */
/* //			else */
/* //				i++; */
/* //			args++; */
/* 		} */
/* 		i++; */
/* 		if (cmd[i] == 34 || cmd[i] == 39) */
/* 			i++; */
/* 		if (!cmd[i] || cmd[i] == 32) */
/* 			args++; */
/* 	} */
/* 	return (args); */
/* } */

/* int	main(void) */
/* { */
/* 	char	*str = "ola eu sou 'esmega coco' lol     lmao'   sakj"; */
/* //	char	*str = "ola eu sou 'esmega coco'lol     lmao'   sakj"; */
/* //	char	*str = "ola eu sou 'esmega coco' lol"; */
/* 	printf("%i\n", get_args(str)); */
/* } */
