/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:57 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/26 11:04:23 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "tokenization.h"

//tokenization
int			class_command(char *cmd, t_env **env);
void		add_token(t_tokens **tokens, t_tokens *new);
void		tokenization(t_tokens **tokens, char *cmd);
t_command	*start_lexer(char *cmd);
int			is_space(char c);
int 		is_operator(char c);
int 		is_quote(char c);
int			which_token(char *cmd, int *i);
t_tokens	*tokenize_word(char *cmd, t_tokens *new, int *i);
void		tokenize_operator(char *cmd, t_tokens *new, int *i);
void		check_quotes(char *cmd, int *i);

//Expander
void	expand_tokens(t_tokens *tokens);
char	*expand_word(char *str);
char	*expand_variable(char **str);
char	*ft_append(char *dest, char c);
void	handle_single_quotes(char **str, char **result);
void	handle_double_quotes(char **str, char **result);
void	handle_dollar(char **str, char **result);

//Command Parsing
t_command	*new_command(void);
void		add_arg(t_command *cmd, char *word);
t_command	*parse_cmd(t_tokens *tokens);
void		redir_out(t_tokens **tokens, t_command *cmd);
void		redir_in_and_heredoc(t_tokens **tokens, t_command *cmd);

// command execution
void	execute_command(t_command *command, t_env **env);
void	execute_redir_out(t_command *cmd);
void	execute_redir_in(t_command *cmd);
void	child_process(t_command *cmd, int pipe_fd[2], int prev_fd, t_env **env);
int		create_pipe(t_command *cmd, int pipe_fd[2]);

// built-in execution
void	echo_builtin(char **argv);
int		cd_builtin(t_command *cmd, t_env **env);
void	get_current_dir();
int		execute_built_in(t_command *cmd);
int		exec_parent_built_in(t_command *cmd, t_env **env);
void	env_bultin(t_env **env, char **envp);
void	add_env_node(t_env **env, char *key, char *value);
void	print_env_list(t_env **env);
char	**env_to_array(t_env *env);
char	*get_env(char *str, t_env **env);
int		ft_strcmp(char *s1, char *s2);
void	export_built_in(t_command *cmd, t_env **env);
void	unset_built_in(t_command *cmd, t_env	**env);
int		is_valid(char *str);

//frees
void	clear_env_list(t_env *env);
void	free_env_array(char **array);
void	free_new(t_tokens *new);
void	free_tokens(t_tokens *tokens);
void	free_command(t_command *cmd);

#endif
