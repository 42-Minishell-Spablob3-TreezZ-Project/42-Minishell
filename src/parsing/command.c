#include "../includes/minishell.h"

t_command *new_command(void)
{
	t_command *cmd;
	
	//setar struct command a 0.
	cmd = ft_calloc(1, sizeof(t_command));
	return (cmd); 
}

//adicionar words do type WORD (realloc dinamico)
void add_arg(t_command *cmd, char *word)
{
	char	**new_argv;
	int		i;
	int		j;

	i = 0;
	while(cmd->argv && cmd->argv[i]) // ["echo"; "hi" ; "joao"];
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
	new_argv[i] = ft_strdup(word); //adiciona nova WORD
	new_argv[i + 1] = NULL; 
	free(cmd->argv);
	cmd->argv = new_argv; 
}
t_command *parse_cmd(t_tokens *tokens)
{
	t_command *cmd;
	t_command *head;

	head = new_command();
	cmd = head;
	while(tokens)
	{
		if (tokens->type == TOKEN_WORD)
			add_arg(cmd, tokens->input);
		else if (tokens->type == TOKEN_PIPE)
		{
			cmd->next = new_command();
			cmd = cmd->next;
		}
		else if (tokens->type == TOKEN_REDIR_OUT || tokens->type == TOKEN_APPEND)
		{
			tokens = tokens->next;
			cmd->outfile = ft_strdup(tokens->input);
			if (tokens->prev->type == TOKEN_APPEND)
				cmd->append = 1;
		}
		else if (tokens->type == TOKEN_REDIR_IN)
		{
			tokens = tokens->next;
			cmd->infile = ft_strdup(tokens->input);
		}
		tokens = tokens->next;
	}
	return (head);
}
