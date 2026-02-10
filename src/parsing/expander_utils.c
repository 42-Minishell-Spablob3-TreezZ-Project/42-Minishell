#include "../includes/minishell.h"

void	handle_single_quotes(char **str, char **result)
{
	(*str)++;
	while (**str && **str != '\'')
	{
		*result = ft_append(*result, **str);
		(*str)++;
	}
	if (**str != '\'')
	{
		printf("Error: unclosed quotes detected.\033[0m\n");
		return ;
	}
	if (**str == '\'')
		(*str)++;
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
	if (**str == '"')
		(*str)++;
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
