#include "../includes/minishell.h"

void execute_command(t_command *cmd, char **envp)
{
	/* printf("command -> %s\n", cmd->argv[0]);
	printf("command -> %s\n", cmd->argv[1]);
	printf("outfile -> %s\n", cmd->outfile);
	printf("infile -> %s\n", cmd->infile);
	printf("append -> %d\n", cmd->append);
 */
	pid_t pid;

	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		printf("----Child Process: child process has started----\n");
		execve("/bin/echo", cmd->argv, envp);
	}
	else
	{
		printf("----Parent Process: parent process is waiting----\n");
		waitpid(pid, NULL, 0); // espera pelo processo child terminar, NULL = no status, 0 = no flags;
		printf("----Child Process: child process terminated----\n");
	}

}