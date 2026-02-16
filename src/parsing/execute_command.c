#include "../includes/minishell.h"

void execute_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	char	*path;

	pid = fork(); // divide o processo em dois (child and parent).
	path = ft_strjoin("/bin/", cmd->argv[0]); // path tem de ser alterado caso (built-ins pedidos).
	if (pid < 0)
	{
		perror("fork!");
		return;
	}
	if (pid == 0)
	{
		if (cmd->outfile)
			execute_redir_out(cmd);
		if (cmd->infile)
			execute_redir_in(cmd);
		execve(path, cmd->argv, envp);
		perror("Minishell");
		exit(1);
	}
	else
		waitpid(pid, NULL, 0); // parent espera que o processo filho termine a execucao.
}

void	execute_redir_out(t_command *cmd)
{
	int	fd;

	if (cmd->outfile && cmd->append == 0)
	{
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("Error: Overwrite");
			exit(1);
		}
		dup2(fd, 1); 
		close(fd);
	}
	else
	{
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("Error: append");
			exit(1);
		}
		dup2(fd, 1); 
		close(fd);
	}
}

void	execute_redir_in(t_command *cmd)
{
	int fd;

	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror("open: infile");
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
}
