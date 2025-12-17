#include "../includes/minishell.h"

t_tokens	*init_list(t_tokens *tokens)
{
	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return NULL;
	tokens->input = NULL;
	tokens->type = 0;
	tokens->next = NULL;
	tokens->prev = NULL;
	return (tokens);
}

int class_tokens(char **results)
{
	int	i;

	i = 0;
	while (results[i])
	{
		if (!ft_strncmp(results[i], "|", INT_MAX))
			printf("TOKEN_PIPE\n");
		else if (!ft_strncmp(results[i], ">", INT_MAX))
			printf("TOKEN_IN\n");
		else if (!ft_strncmp(results[i], "<", INT_MAX))
			printf("TOKEN_OUT\n");
		else if (!ft_strncmp(results[i], ">>", INT_MAX))
			printf("TOKEN_APPEND\n");
		else if (!ft_strncmp(results[i], "<<", INT_MAX))
			printf("TOKEN_HEREDOC\n");
		else
			printf ("TOKEN_WORD\n");
		i++;
	}
	return (0);
}

char	*parse_command(char *cmd)
{
	int			i;
	char		**results;
	t_tokens	*tokens;

	i = 0;
	tokens = NULL;
	if (!cmd)
		return NULL;
	tokens = init_list(tokens);
	ft_printf("%s\n", tokens->input);
	results = ft_split(cmd, ' ');
	class_tokens(results);

	return (results[0]);
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
