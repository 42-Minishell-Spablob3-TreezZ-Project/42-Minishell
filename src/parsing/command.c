/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:54:55 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/27 17:23:22 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	return (cmd);
}

/* static void	*ft_realloc(void *ptr, size_t size) */
/* { */
/* 	void	*new_ptr; */

/* 	if (ptr == NULL) */
/* 		return (malloc(size)); */
/* 	if (!size) */
/* 		return (ptr); */
/* 	new_ptr = malloc(size); */
/* 	ft_memcpy(new_ptr, ptr, size); */
/* 	return (new_ptr); */
/* } */

static int	add_arg(t_command *cmd, t_tokens *tokens)
{
	//char		**new_argv;
	t_tokens	*temp;
	int			len;
	int			words;

	temp = tokens;
	len = 0;
	while (temp && temp->input)
	{
		temp = temp->next;
		len++;
	}
	cmd->argv = malloc(len * sizeof(char *));
	words = 0;
	//temp = tokens;
	while (words < len && tokens->type == TOKEN_WORD)
	{
		cmd->argv[words] = ft_strdup(tokens->input);
		tokens = tokens->next;
		words++;
	}
	return (words);
	//cmd->argv = new_argv;
	//free(new_argv);
	//printf("%i\n", len);

	/* char	**new_argv; */
	/* int		i; */
	/* int		j; */

	/* i = 0; */
	/* new_argv = NULL; */
	/* if (!cmd->argv) */
	/* { */
	/* 	new_argv = ft_realloc(new_argv, i); */
	/* 	new_argv[i] = ft_strdup(word); */
	/* 	if (!cmd->argv) */
	/* 		cmd->argv = new_argv; */
	/* 	else */
	/* 		cmd->argv[i] = new_argv[i]; */
	/* } */
	/* j = 0; */
	/* while (cmd->argv && cmd->argv[j]) */
	/* 	j++; */
	/* if (j > 0) */
	/* 	i = j - 1; */
	/* while (i < j) */
	/* { */
	/* 	if (!cmd->argv[i]) */
	/* 		break ; */
	/* 	new_argv = ft_realloc(new_argv, i); */
	/* 	new_argv[i] = ft_strdup(word); */
	/* 	if (!cmd->argv) */
	/* 		cmd->argv = new_argv; */
	/* 	else */
	/* 		cmd->argv[i] = new_argv[i]; */
	/* 	i++; */
	/* } */

	/* char	**new_argv; */
	/* int		i; */

	/* i = 0; */
	/* while (cmd->argv && cmd->argv[i]) */
	/* 	i++; */
	/* new_argv = ft_realloc(cmd->argv, i); */
	/* new_argv[i] = ft_strdup(word); */
	/* if (!cmd->argv) */
	/* 	cmd->argv = new_argv; */
	/* else */
	/* 	cmd->argv[i] = new_argv[i]; */
	
	/* char	**new_argv; */
	/* int		i; */
	/* int		j; */

	/* i = 0; */
	/* new_argv = NULL; */
	/* while (cmd->argv && cmd->argv[i]) */
	/* 	i++; */
	/* j = 0; */
	/* while (new_argv && new_argv[j]) */
	/* { */
	/* 	if (new_argv[j]) */
	/* 		free(new_argv[j]); */
	/* 	j++; */
	/* } */
	/* if (new_argv) */
	/* 	free(new_argv); */
	/* new_argv = malloc((i + 2) * sizeof(char *)); */
	/* if (!new_argv) */
	/* 	return ; */
	/* j = 0; */
	/* while (j < i) */
	/* { */
	/* 	new_argv[j] = cmd->argv[j]; */
	/* 	j++; */
	/* } */
	/* new_argv[i] = ft_strdup(word); */
	/* new_argv[i + 1] = NULL; */
	/* /\* i = 0; *\/ */
	/* /\* while (cmd->argv && cmd->argv[i]) *\/ */
	/* /\* { *\/ */
	/* /\* 	if (cmd->argv[i]) *\/ */
	/* /\* 		free(cmd->argv[i]); *\/ */
	/* /\* 	i++; *\/ */
	/* /\* } *\/ */
	/* free(cmd->argv); */
	/* cmd->argv = new_argv; */
}

t_command	*parse_cmd(t_tokens *tokens)
{
	t_command	*cmd;
	t_command	*head;
	int			words;
	int			i;

	i = 0;
	head = new_command();
	cmd = head;
	while (tokens && tokens->input)
	{
		if (tokens->type == TOKEN_WORD)
		{
			words = add_arg(cmd, tokens);
			while (i < words)
			{
				tokens = tokens->next;
				i++;
			}
		}
		else if (tokens->type == TOKEN_PIPE)
		{
			cmd->next = new_command();
			cmd = cmd->next;
		}
		else if (tokens->type == TOKEN_REDIROUT || tokens->type == TOKEN_APPEND)
			redir_out(&tokens, cmd);
		else if (tokens->type == TOKEN_REDIRIN || tokens->type == TOKEN_HEREDOC)
			redir_in_and_heredoc(&tokens, cmd);
		if (tokens)
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
