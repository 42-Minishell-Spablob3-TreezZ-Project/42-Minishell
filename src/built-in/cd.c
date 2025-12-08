#include "../includes/minishell.h"

void	change_directory(char *str)
{
	char	*dir;

	dir = NULL;
	if (str == NULL)
	{
		dir = ft_strjoin("/home/", getenv("USER"));
		chdir(dir);
		free(dir);
	}
	else
		chdir(str);
}

/* int	main(void) */
/* { */
/* 	char	*str = NULL; */

/* 	printf("%s\n", getcwd(str, 100)); */
/* 	change_directory(NULL); */
/* 	printf("%s\n", getcwd(str, 100)); */
/* 	return (0); */
/* } */

/* char	*ft_strjoin(char const *s1, char const *s2) */
/* { */
/* 	char	*news; */
/* 	int		c1; */
/* 	int		c2; */

/* 	c1 = 0; */
/* 	c2 = 0; */
/* 	news = calloc(((strlen(s1) + strlen(s2)) + 1), sizeof(char)); */
/* 	if (!news) */
/* 		return (NULL); */
/* 	while (s1[c1] != '\0') */
/* 	{ */
/* 		news[c1] = s1[c1]; */
/* 		c1++; */
/* 	} */
/* 	while (s2[c2] != '\0') */
/* 	{ */
/* 		news[c1] = s2[c2]; */
/* 		c1++; */
/* 		c2++; */
/* 	} */
/* 	news[c1] = '\0'; */
/* 	return (news); */
/* } */

/* Make readline in start_shell function default to the /home/$USER path.
 If we want to get fancy, we can spawn a second readline displaying
which directory we are in, but maybe won't work. We'll see.*/

//Additional function to add somewhere else:

char	*trim_dir(char *dir)
{
	char	*result;
	char	*comparison;
	int		i;

	result = dir;
	comparison = "/home/gonzo";
	i = 0;
	while (result[i] == comparison[i])
		i++;
	result = ft_strjoin("~", &result[i]);
	return (result);
}

/* int	main(void) */
/* { */
/* 	printf("%s\n", trim_dir("/home/gonzo/Desktop")); */
/* 	return (0); */
/* } */

//Modified shell.c functions to implement after:

/* char	*create_prompt(void) */
/* { */
/* 	char	*prompt; */
/* 	char	*dir; */

/* 	prompt = "@minisheila:"; */
/* 	prompt = ft_strjoin(getenv("USER"), prompt); */
/* 	dir = NULL; */
/* 	dir = getcwd(dir, INT_MAX); */
/* 	dir = trim_dir(dir); */
/* 	dir = ft_strjoin(dir, ">$ "); */
/* 	prompt = ft_strjoin(prompt, dir); */
/* 	free(dir); */
/* 	return (prompt); */
/* } */

//Find way to rerun create_prompt whenever a cd command happens

/* void	start_shell(void) */
/* { */
/* 	char	*command; */
/* 	char	*prompt; */
/* //	char	*result; */

/* 	command = NULL; */
/* 	prompt = create_prompt(); */
/* 	while (1) */
/* 	{ */
/* 		command = readline(prompt); */
/* 		if (!class_command(command)) */
/* 		{ */
/* 			free (command); */
/* 			break ; */
/* 		} */
/* 		add_history(command); */
/* //		prompt = create_prompt(command); */
/* 		free (command); */
/* 	} */
/* 	free (prompt); */
/* } */
