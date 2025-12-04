#include "../includes/minishell.h"

int	verify_next(char *string, int i, char limiter)
{
	while (string[i] == limiter)
		i++;
	if (isalpha(string[i]))
			return (0);
	else if (string[i] == '"')
		return (i);
	return (0);
}

int	check_quotation(char *string, int i)
{
	if (string[i] == '"')
	{
		i++;
		while (string[i] != '"' && string[i])
			i++;
		if (!string[i])
			return (0);
		else if (string[i] == '"' && string[i + 1])
			i++;
		else
		{
			i++;
			return (i);
		}
	}
	return (i);
}

int	custom_word_count(char *string, char limiter)
{
	int	i;
	int	check;
	int	count;

	i = 0;
	count = 0;
	while (string[i])
	{
		check = 0;
		while (string[i] == limiter)
			i++;
		if (string[i])
			count++;
		while (string[i] != limiter && string[i] != '"' && \
string[i])
			i++;
		if (string[i] == ' ' && verify_next(string, i, limiter))
		{
			i = verify_next(string, i, limiter);
			check = check_quotation(string, i);
		}
		else if (string[i] == '"')
			check = check_quotation(string, i);
		if (check && string[check])
		{
			i = check;
			count++;
		}
		else
//			i = check - 1;
			i = i + check;
	}
	return (count);
}

int	main(void)
{
	char	*str;
	int		i;

	str = readline("Boas: ");
	i = custom_word_count(str, ' ');
	printf("%d\n", i);
	return (0);
}

/* int	custom_word_count(char *string, char limiter) */
/* { */
/* 	int	i; */
/* 	int	count; */

/* 	i = 0; */
/* 	count = 0; */
/* 	while (string[i]) */
/* 	{ */
/* 		while (string[i] == limiter) */
/* 			i++; */
/* 		if (string[i]) */
/* 			count++; */
/* 		if (string[i] == '"') */
/* 		{ */
/* 			while (string[i] != '"' && string[i]) */
/* 				i++; */
/* 			if (!string[i]) */
/* 				return (0); */
/* 			else if (string[i] == '"') */
/* 			{ */
/* 				i++; */
/* 				count++; */
/* 			} */
/* 		} */
/* 		while (string[i] != limiter && string[i]) */
/* 			i++; */
/* 	} */
/* 	return (count); */
/* } */
