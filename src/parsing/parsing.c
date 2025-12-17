#include "../includes/minishell.h"

int class_tokens(char **results)
{
	int	i;

	i = 0;
	while (results[i])
	{
		if (!strcmp(results[i], "|"))
			printf("TOKEN_PIPE\n");
		else if (!strcmp(results[i], ">"))
			printf("TOKEN_IN\n");
		else if (!strcmp(results[i], "<"))
			printf("TOKEN_OUT\n");
		else if (!strcmp(results[i], ">>"))
			printf("TOKEN_APPEND\n");
		else if (!strcmp(results[i], "<<"))
			printf("TOKEN_HEREDOC\n");
		else
			printf ("TOKEN_WORD\n");
		i++;
	}
	return (0);
}

char	*parse_command(char *cmd)
{
	int		i;
	char	**results;

	i = 0;
	if (!cmd)
		return NULL;
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
