#include "../includes/minishell.h"

// Ponteiro para o previous node 
void	add_token(t_tokens **tokens, t_tokens *new)
{
	t_tokens	*last;

	new->next = NULL;
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
	t_command 	*command;
	t_tokens	*tokens;
	char		*result;

	tokens = NULL;
	if (!cmd)
		return (NULL);
	start_lexer(&tokens, cmd);
	expand_tokens(tokens);
	command = parse_cmd(tokens);
	if (tokens->input)
	{
		result = ft_strdup(tokens->input);
		free_tokens(tokens);
		return (result);
	}
	free(tokens);
	return (0); //Apenas retorna primeiro node (não precisamo de retornar)
}

int	class_command(char *cmd, char **envp)
{
	char	*parsed;

	parsed = parse_command(cmd);
	if (!parsed)
		return (0);
	if (ft_strncmp (parsed, "exit", INT_MAX) == 0)
	{
		free(parsed);
		return (0);
	}
	else if (parsed)
	{
		execute_command(parsed, envp);
		free(parsed);
	}
	return (1);
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->input);
		free(tokens);
		tokens = tmp;
	}
}
