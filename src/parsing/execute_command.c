/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:48:47 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/05 13:39:45 by joapedro         ###   ########.fr       */
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
	t_heredoc *tmp;

	prev_fd = -1;
	while (cmd)
	{
		process_heredoc(cmd);
		if (create_pipe(cmd, pipe_fd) < 0)
			return ;
		if (exec_parent_built_in(cmd, env) == 0)
			return ;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
			child_process(cmd, pipe_fd, prev_fd, env);
		if (prev_fd != -1)
			close(prev_fd);//fechar pipe anterior;
		if (cmd->heredocs)
		{
			tmp = cmd->heredocs;
			while (tmp)
			{
				close(tmp->fd[0]);
				tmp = tmp->next;
			}
		}
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

static char	*check_path(char **path_array, t_command *cmd)
{
	char	*dir_plus_bar;
	int		i;
	char	*result;
		
	i = 0;
	while (path_array[i])
	{
		dir_plus_bar = ft_strjoin(path_array[i], "/");
		result = ft_strjoin(dir_plus_bar, cmd->argv[0]);
		free(dir_plus_bar);
		if (access(result, X_OK) == 0)
		{
			free_array(path_array);
			return(result);
		}
		free(result);
		i++;
	}
	free_array(path_array);
	return (NULL);
}

static char	*find_path(t_command *cmd, t_env **env)
{
	char	*result;
	t_env	*temp;
	char	**path_array;
	
	temp = *env;
	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (access(cmd->argv[0], X_OK) == 0) //verifica se o ficheiro existe e se e executavel -> (X_OK)
			return(result = ft_strdup(cmd->argv[0]));
		else
			return (NULL);
	}
	while (temp)
	{
		if (ft_strcmp(temp->key, "PATH") == 0)
		{
			path_array = ft_split(temp->value, ':');
			if (!path_array)
				return (NULL);
			return (check_path(path_array, cmd));
		}
		temp = temp->next;
	}
	return (NULL);
}

void	child_process(t_command *cmd, int pipe_fd[2], int prev_fd, t_env **env)
{
	char		*path;
	char		**env_array;
	t_heredoc	*temp;
	
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0); //redireciona STDIN para o pipe.
		close(prev_fd); // fechar o fd do comando anterior original.
	}
	if (cmd->heredocs)
	{
		temp = cmd->heredocs;
		while (temp->next)
			temp = temp->next;
		dup2(temp->fd[0], 0);
		close (temp->fd[0]);
	}	
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
	if (execute_built_in(cmd))// pwd e echo. restantes bultins executados no pai para haver alteracoes.
	{
		free_command(cmd);
		clear_env_list(env);
		exit(0); // fazer uma funcao exit em que da free em tudo.
	}
	path = find_path(cmd, env); // MUDAR! search na variavel PATH
	env_array = env_to_array(*env);
	if (path)
	{
		execve(path, cmd->argv, env_array);
		free(path);
	}
	perror("execve failed");
	g_exit_status = 2;
	free_array(env_array); //dar free na env_array; (por no exit function)
	clear_env_list(env);
	free_command(cmd);
	exit(1);
}

void	execute_redir_out(t_command *cmd)
{
	int	fd;

	if (cmd->outfile && cmd->append == 0)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, 1); // criar condicao no caso de falhar o dup ??
	close(fd);
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
