#include "includes/minishell.h"

volatile sig_atomic_t g_sigint = 0;

char	*create_prompt(void)
{
	char	*prompt;

	prompt = "@minisheila>$ ";
	prompt = ft_strjoin(getenv("USER"), prompt);
	return (prompt);
}

void	start_shell(void)
{
	char	*command;
	char	*prompt;

	command = NULL;
	prompt = create_prompt();
	while (1)
	{
		command = readline(prompt);
		// CTRL-C
		if (!command && g_sigint)
		{
			g_sigint = 0;
			continue ;
		}
		// CTRL-D
		if (!command)
		{
			printf("exit\n");
			break ;
		}
		if (*command == '\0')
		{
			free(command);
			continue;
		}
		class_command(command);
		add_history(command);
		free (command);
	}
	free (prompt);
}

//enum { MAXC = 128 };

/* void	write_history(int) */
/* { */
/* 	add_history */
/* } */

/* int main (void){ */

/*     char ps[MAXC] = "", */
/*         *p = getenv("USER"), */
/*         *host = getenv("HOSTNAME"), */
/*         *s = NULL; */
/*     int count = 1; */
/*     sprintf(ps, "%d %s@%s> ", count, p, host); */
/* //	CHECK WHAT THIS DOES PROPERLY */
/*     using_history();    /\* initialize history *\/ */

/*     while ((s = readline(ps))) { */
/*         if (strcmp (s, "quit") == 0) { */
/*             free (s); */
/*             break; */
/*         } */
/*         add_history (s); */
/*         free (s); */
/*         count++; */
/*         sprintf (ps, "%d %s@%s> ", count, p, host); */
/*     } */
/* } */
