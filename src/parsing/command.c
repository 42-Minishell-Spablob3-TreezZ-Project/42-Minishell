/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:54:55 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/24 15:08:21 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return NULL;
	return (cmd);
}

void	add_arg(t_command *cmd, char *word)
{
	char	**new_argv;
	int		i;
	int		j;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		i++;
	new_argv = malloc((i + 2) * sizeof(char *));
	if (!new_argv)
		return ;
	j = 0;
	while (j < i)
	{
		new_argv[j] = cmd->argv[j];
		j++;
	}
	new_argv[i] = ft_strdup(word);
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

t_command	*parse_cmd(t_tokens *tokens)
{
	t_command	*cmd;
	t_command	*head;

	head = new_command();
	cmd = head;
	while (tokens && tokens->input)
	{
		if (tokens->type == TOKEN_WORD)
			add_arg(cmd, tokens->input);
		else if (tokens->type == TOKEN_PIPE)
		{
			cmd->next = new_command();
			cmd = cmd->next;
		}
		else if (tokens->type == TOKEN_REDIROUT || tokens->type == TOKEN_APPEND)
			redir_out(&tokens, cmd);
		else if (tokens->type == TOKEN_REDIRIN || tokens->type == TOKEN_HEREDOC)
			redir_in_and_heredoc(&tokens, cmd);
		tokens = tokens->next;
	}
	return (head);
}

void	redir_out(t_tokens **tokens, t_command *cmd)
{
	(*tokens) = (*tokens)->next;
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = ft_strdup((*tokens)->input);
	if ((*tokens)->prev->type == TOKEN_APPEND)
		cmd->append = 1;
	else
		cmd->append = 0;
}

void	redir_in_and_heredoc(t_tokens **tokens, t_command *cmd)
{
	(*tokens) = (*tokens)->next;
	if (cmd->infile)
		free(cmd->infile);
	if ((*tokens)->prev->type == TOKEN_REDIRIN)
		cmd->infile = ft_strdup((*tokens)->input);
	else
		cmd->heredoc_delimiter = ft_strdup((*tokens)->input);
}
