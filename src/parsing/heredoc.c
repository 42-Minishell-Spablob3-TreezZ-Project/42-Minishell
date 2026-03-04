

#include "../includes/minishell.h"

void	add_heredoc(t_tokens *tokens, t_command *cmd)
{
	t_heredoc	*new;
	t_heredoc	*temp;

	new = malloc(sizeof(t_heredoc));
	if(!new)
		return ;
	new->delimiter = ft_strdup(tokens->input);
	new->fd[0]	= -1;
	new->fd[1] = -1;
	new->next = NULL;

	if (cmd->heredocs == NULL)
		cmd->heredocs = new;
	else
	{
		temp = cmd->heredocs;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int	process_heredoc(t_command *cmd)
{
	t_heredoc	*temp;
	t_heredoc	*last;
	char		*line;

	temp = cmd->heredocs;
	if (!temp)
		return (0);
	while (temp)
	{
		last = temp;
		temp = temp->next;
	}
	temp = cmd->heredocs;
	while (temp)
	{
		if (pipe(temp->fd) < 0)
		{
			perror("pipe");
			return (-1);
		}
		while (1)
		{
			line = readline("> ");
			if (line == NULL || ft_strcmp(line, temp->delimiter) == 0)
			{
				free(line);
				break ;
			}
			if (temp == last)
			{
				write(temp->fd[1], line,ft_strlen(line));
				write(temp->fd[1], "\n", 1);
			}
			free(line);
		}
		close(temp->fd[1]);
		temp = temp->next;
	}
	return (0);
}
