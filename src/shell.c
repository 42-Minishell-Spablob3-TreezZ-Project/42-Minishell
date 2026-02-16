#include "includes/minishell.h"

volatile sig_atomic_t	g_sigint = 0;

char	*create_prompt(void)
{
	char	*prompt;

	prompt = "@minisheila>$ ";
	prompt = ft_strjoin(getenv("USER"), prompt);
	return (prompt);
}

void	start_shell(char **envp)
{
	char	*command;
	char	*prompt;

	command = NULL;
	prompt = create_prompt();
	while (1)
	{
		command = readline(prompt);
		if (!class_command(command, envp))
		{
			free (command);
			printf("exit\n");
			break ;
		}
		add_history(command);
		free (command);
	}
	free (prompt);
}
