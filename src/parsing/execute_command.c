/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:48:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/24 11:25:53 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_command(t_command *cmd, t_env **env)
{
	//retornar exit_status assim que o comando foi executado ou nao.
	//guardar o valor do last pid (valor do ultimo processo) no parent para depois retornar o seu exit_status
	//só deve retornar exit_status do ultimo comando EX: ls | wc --> o exit status é referente ao wc.
	
	//comando ok	0
	//erro genérico	1
	//command not found	127
	//Ctrl+C	130
	//Ctrl+\	131
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (cmd)
	{
		if (create_pipe(cmd, pipe_fd) < 0)
			return ;
		if (exec_parent_built_in(cmd, env) == 0)
			return ;
		pid = fork(); //dividir o processo em pai e filho
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
			child_process(cmd, pipe_fd, prev_fd, env);
		if (prev_fd != -1)
			close(prev_fd);//fechar pipe anterior;
		if (cmd->next)
		{
			close(pipe_fd[1]);//fechar o write
			prev_fd = pipe_fd[0]; //read para o proximo comando
		}
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);
}

int	create_pipe(t_command *cmd, int pipe_fd[2])
{
	if (cmd->next)// se houver cmd->next, criar pipe
	{	
		if (pipe(pipe_fd) < 0)
		{
			perror("pipe"); // funcao pipe retorna 0 se bem sucedida e -1 em caso de erro.
			return (-1);
		}
	}
	return (0);
}

void	child_process(t_command *cmd, int pipe_fd[2], int prev_fd, t_env **env)
{
	char	*path;
	char	**env_array;
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
		close(pipe_fd[0]); // fecha o pipe 
		close(pipe_fd[1]);
	}
	if (cmd->outfile || cmd->append)
		execute_redir_out(cmd);
	if (cmd->infile)
		execute_redir_in(cmd);
	execute_built_in(cmd, env); // pwd e echo. restantes bultins executados no pai para haver alteracoes.
	path = ft_strjoin("/usr/bin/", cmd->argv[0]);
	env_array = env_to_array(*env);
	execve(path, cmd->argv, env_array);
	perror("execve failed");
	free_env_array(env_array); //dar free na env_array;
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
