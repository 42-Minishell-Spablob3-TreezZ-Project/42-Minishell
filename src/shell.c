#include "includes/minishell.h"

volatile sig_atomic_t	g_sigint = 0;

char	*get_prompt_host(char *prompt)
{
	int		i;
	char	*host;

	i = 0;
	while (prompt[i] != '.')
		i++;
	host = malloc(i * sizeof(char *));
	i = 0;
	while (prompt[i] != '.')
	{
		host[i] = prompt[i];
		i++;
	}
	prompt = ft_strjoin(getenv("USER"), \
ft_strjoin("@", ft_strjoin(host, ">$ ")));
	free(host);
	return (prompt);
}

char	*create_prompt(void)
{
	char	*prompt;
	char	buf[256];
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	read(fd, buf, 256);
	prompt = buf;
	if (prompt[0] == 'c')
	{
		prompt = get_prompt_host(prompt);
	}
	else
		prompt = ft_strjoin(getenv("USER"), \
ft_strjoin("@", ft_strjoin(prompt, ">$ ")));
	close(fd);
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
			printf("exit\n");
			break ;
		}
		add_history(command);
		free (command);
	}
	free (prompt);
}

//enum { MAXC = 128 };

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
