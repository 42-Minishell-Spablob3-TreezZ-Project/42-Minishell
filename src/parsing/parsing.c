#include "../includes/minishell.h"

int	class_command(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp (cmd, "exit", INT_MAX) == 0)
		return (0);
	return (1);
}
