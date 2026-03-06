/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:00 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/06 11:10:39 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	process_heredoc(t_heredoc *temp, t_heredoc *last)
{
	char		*line;

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
}

int	init_heredoc(t_command *cmd)
{
	t_heredoc	*temp;
	t_heredoc	*last;

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
		process_heredoc(temp, last);
		temp = temp->next;
	}
	return (0);
}

void	dup_heredoc(t_command *cmd)
{
	t_heredoc	*temp;

	temp = cmd->heredocs;
	while (temp->next)
		temp = temp->next;
	dup2(temp->fd[0], 0);
	close (temp->fd[0]);
}