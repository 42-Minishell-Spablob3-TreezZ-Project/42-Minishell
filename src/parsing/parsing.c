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

// Ponteiro para o previous node 
void	add_token(t_tokens **tokens, t_tokens *new)
{
	t_tokens	*last;

	if (!(*tokens))
	{
		*tokens = new;
		new->prev = NULL;
		return ;
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	start_lexer(t_tokens **tokens, char *cmd)
{
	int			i;
	t_tokens	*new;

	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && is_space(cmd[i]))
			i++;
		if (!cmd[i])
			break ;
		new = ft_calloc(1, sizeof(t_tokens));
		if (is_operator(cmd[i]))
			tokenize_operator(cmd, new, &i);
		else
			tokenize_word(cmd, new, &i);
		add_token(tokens, new);
	}
}

//ALTERAR FUNCAO PARA START LEXER
char	*parse_command(char *cmd)
{
	t_tokens	*tokens;

	tokens = NULL;
	if (!cmd)
		return NULL;
	start_lexer(&tokens, cmd);
	expand_tokens(tokens);
	return (tokens->input); //Apenas retorna primeiro node (não precisamo de retornar)
}

int	class_command(char *cmd)
{
	char	*parsed;

	parsed = parse_command(cmd); //Chamar start lexer
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
