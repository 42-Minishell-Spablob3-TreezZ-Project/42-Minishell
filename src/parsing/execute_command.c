#include "../includes/minishell.h"

void execute_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	path = ft_strjoin("/bin/", cmd->argv[0]);
	if (pid < 0)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		//printf("----Child Process: child process has started----\n");
		execve(path, cmd->argv, envp);
		perror("execve");
		exit(1);
	}
	else
	{
		//printf("----Parent Process: parent process is waiting----\n");
		waitpid(pid, NULL, 0); // espera pelo processo child terminar, NULL = no status, 0 = no flags;
		//printf("----Child Process: child process terminated----\n");
	}

}