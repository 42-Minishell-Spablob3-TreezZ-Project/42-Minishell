#include "../includes/minishell.h"

t_tokens	*tokenize_operator(char *cmd, t_tokens *new, int *i)
{
	if (cmd[*i] == '|')
		new->type = TOKEN_PIPE;
	if (cmd[*i] == '<')
	{
		if (cmd[*i + 1] == '<')
			new->type = TOKEN_HERE_DOC;
		else
			new->type = TOKEN_REDIR_IN;
	}
	if (cmd[*i] == '>')
	{
		if (cmd[*i + 1] == '>')
			new->type = TOKEN_APPEND;
		else
			new->type = TOKEN_REDIR_OUT;
	}
	new->input = cmd;
	return (new);
}

t_tokens	*tokenize_word(char *cmd, t_tokens *new, int *i)
{
	new->type = TOKEN_WORD;
	while (cmd[*i] && !is_space(cmd[*i]) && !is_operator(cmd[*i]))
		check_quotes(cmd, i);
	new->input = cmd;
	return (new);
}

void	check_quotes(char *cmd, int *i)
{
	char	quote;
	
	if (is_quote(cmd[*i]))
	{
		quote = cmd[*i];
		(*i)++;
		while (cmd[*i] && cmd[*i] != quote)
			(*i)++;
		if (cmd[*i] && cmd[*i] == quote)
			(*i)++;
	}
	else
	{
		while (cmd[*i] && !is_space(cmd[*i]) && !is_operator(cmd[*i]))
			(*i)++;
	}
}

int	which_token(char *cmd, int *i)
{
	if (cmd[*i] == 32 || (cmd[*i] >= 9 && cmd[*i] <= 13))
		(*i)++;
	else if (cmd[*i] == '|' || cmd[*i] == '>' || cmd[*i] == '<')
		return (0);
	return (1);
}

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int is_operator(char c)
{
    return (c == '|' || c == '>' || c == '<');
}

int is_quote(char c)
{
    return (c == '"' || c == '\'');
}

/* #include <stdio.h> */

/* int	main(void) */
/* { */
/* 	char	*str = "hello > yo"; */
/* 	int	i = 0; */
/* 	while (str[i]) */
/* 		printf("%i\n", which_token(str, &i)); */
/* 	return (0); */
/* } */
