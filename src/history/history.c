#include "../includes/minishell.h"

char	*create_prompt(void)
{
	char	*prompt;

	prompt = "@hist_test>$ ";
	prompt = ft_strjoin(getenv("USER"), prompt);
	return (prompt);
}

void	hist_test(void)
{
	char	*line;
	char	*prompt;

	line = NULL;
	prompt = create_prompt();
	while (1)
	{
		line = readline(prompt);
		if (ft_strncmp (line, "exit", INT_MAX) == 0)
		{
			free (line);
			break ;
		}
		add_history(line);
		free (line);
	}
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
