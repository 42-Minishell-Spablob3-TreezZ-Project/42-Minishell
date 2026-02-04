#include "../includes/minishell.h"

void	handle_single_quotes(char **str, char **result)
{
	// se carater anterior for duplas aspas seguido de aspas singulares e $. tenho que tratar $
	/* if (*(*str - 1) == '"')
		handle_double_quotes(str, result); */
	(*str)++; // salto primeras aspas.
	while (**str && **str != '\'')
	{
		*result = ft_append(*result, **str); // percorro carateres e faço append.
		(*str)++;
	}
	if (**str != '\'')
	{
		printf("Error: unclosed quotes detected.\033[0m\n");
		return ;
	}
// no caso da string nao tiver sido fechada com aspas. Ex: '$USER
	/* if (**str == '\'') // salto ultimas aspas.
		(*str)++; */
}
void	handle_double_quotes(char **str, char **result)
{
	(*str)++;
	while (**str && **str != '"')
	{
		if (**str == '$')
			handle_dollar(str, result);
		else 
		{
			*result = ft_append(*result, **str);
			(*str)++;
		}
	}
	if (**str != '"')
	{
		printf("Error: unclosed quotes detected.\033[0m\n");
		return ;
	}
}

void	handle_dollar(char **str, char **result)
{
	char	*expanded;

	expanded = expand_variable(str);
	if (expanded)
	{
		if (!result)
			return ;
		*result = ft_strjoin(*result, expanded);
		free(expanded);
	}
}
