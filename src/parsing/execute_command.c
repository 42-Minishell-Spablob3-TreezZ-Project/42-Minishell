#include "../includes/minishell.h"

void execute_command(t_command *cmd, char **envp)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next) // se houver cmd->next, criar pipe
			pipe(pipe_fd);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
			child_process(cmd, pipe_fd, prev_fd, envp);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);

}

void	child_process(t_command *cmd, int pipe_fd[2], int prev_fd, char **envp)
{
	char	*path;
	// se houver comando anterior
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0); //redireciona STDIN para o pipe.
		close(prev_fd); // fechar o fd do comando anterior original.
	}
	// se houver proximo comando
	if (cmd->next)
	{
		dup2(pipe_fd[1], 1); //redireciona STDOUT para novo pipe.
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (cmd->outfile || cmd->append)
		execute_redir_out(cmd);
	if (cmd->infile)
		execute_redir_in(cmd);
	path = ft_strjoin("/bin/", cmd->argv[0]);
	execve(path, cmd->argv, envp);
	perror("Minisheila");
	exit(1);
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
	int	fd;

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
