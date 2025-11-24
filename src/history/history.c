#include "../includes/minishell.h"

enum { MAXC = 128 };

char	*create_prompt(void)
{
	char	*user;
	char	*host;
	char	*prompt;

	user = getenv("USER");
	host = "hist_test>$ ";
	prompt = ft_strjoin("@", host);
	prompt = ft_strjoin(user, prompt);
	prompt = ft_strjoin(" ", prompt);
	return (prompt);
}

void	hist_test(void)
{
    char	*ps;
	char	*s;
	char	*prompt;
	int		count;

	s = NULL;
	count = 1;
	prompt = create_prompt();
	ps = ft_strjoin(ft_itoa(count), prompt);
//	ft_printf("%s\n", ps);
//	sprintf(ps, "%d %s@%s> ", count, p, host);
    using_history();    /* initialize history */
    while ((s = readline(ps)))
	{
        if (strcmp (s, "exit") == 0)
		{
            free (s);
            break;
        }
		add_history (s);
		free (s);
		count++;
		ps = ft_strjoin(ft_itoa(count), prompt);
//		sprintf (ps, "%d %s@%s> ", count, p, host);
	}
}

/* void	write_history(int) */
/* { */
/* 	add_history */
/* } */

/* int main (void){ */

/*     char ps[MAXC] = "",  */
/*         *p = getenv("USER"), */
/*         *host = getenv("HOSTNAME"), */
/*         *s = NULL;  */
/*     int count = 1; */
/*     sprintf(ps, "%d %s@%s> ", count, p, host); */

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
