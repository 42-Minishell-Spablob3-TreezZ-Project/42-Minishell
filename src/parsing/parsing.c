#include "../includes/minishell.h"

/* void	start_lexer(t_tokens **tokens, char *cmd) */
/* { */
/* 	int			i; */
/* 	t_tokens	*new; */

/* 	i = 0; */
/* 	new = NULL; */
/* 	while (cmd[i]) */
/* 	{ */
/* 		if (cmd[i] == 32 || (cmd[i] >= 9 && cmd[i] <= 13)) */
/* 			i++; */
/* 		is_operator(cmd[i]); */
/* 			tokenize_operator(cmd, new, &i); */
/* 		else */
/* 			tokenize_word(cmd, new, &i); */
/* 	} */
/* } */

void	add_token(t_tokens **tokens, t_tokens *new)
{
	t_tokens	*temp;

	if (!(*tokens))
	{
		*tokens = new;
		return ;
	}
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	start_lexer(t_tokens **tokens, char *cmd)
{
	int			i;
	int			which;
	t_tokens	*new;

	i = 0;
	new = NULL;
	while (cmd[i])
	{
		which = which_token(cmd, &i);
		if (!which)
			tokenize_operator(cmd, new, &i);
		else
			tokenize_word(cmd, new, &i);
		add_token(tokens, new);
	}
}

char	*parse_command(char *cmd)
{
	int			i;
	t_tokens	*tokens;

	i = 0;
	tokens = NULL;
	if (!cmd)
		return NULL;
	//Initialize token struct with all values to NULL
	tokens = ft_calloc(1, sizeof(tokens));
	start_lexer(&tokens, cmd);
	return (tokens->input);
}

int	class_command(char *cmd)
{
	char	*parsed;

	parsed = parse_command(cmd);
	if (!parsed)
		return (0);
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
