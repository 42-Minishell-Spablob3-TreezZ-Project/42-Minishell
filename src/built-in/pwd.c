#include "../includes/minishell.h"


	// implementar forma de executar a funcao get_current_dir
	
	/* if (ft_strncmp (cmd, "pwd", INT_MAX) == 0)
	{
		get_current_dir();
		return(0);
	} */


void get_current_dir()
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
}