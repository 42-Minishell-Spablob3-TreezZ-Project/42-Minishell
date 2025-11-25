#include "includes/minishell.h"

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
		if (!class_command(command))
		{
			free (command);
			break ;
		}
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
