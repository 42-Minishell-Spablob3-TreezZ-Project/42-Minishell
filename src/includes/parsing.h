/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:57 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/11 17:29:57 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "tokenization.h"

//tokenization
int			class_command(char *cmd, t_env **env);
void		add_token(t_tokens **tokens, t_tokens *new);
void		tokenization(t_tokens **tokens, char *cmd);
t_command	*start_lexer(char *cmd, t_env **env);
int			is_space(char c);
int			is_operator(char c);
int			is_quote(char c);
int			which_token(char *cmd, int *i);
t_tokens	*tokenize_word(char *cmd, t_tokens *new, int *i);
void		tokenize_operator(char *cmd, t_tokens *new, int *i);
void		check_quotes(char *cmd, int *i);

//Expander
void		expand_tokens(t_tokens *tokens, t_env **env);
char		*expand_word(char *str, t_env **env);
char		*expand_variable(char **str, t_env **env);
char		*ft_append(char *dest, char c);
void		handle_single_quotes(char **str, char **result);
void		handle_double_quotes(char **str, char **result, t_env **env);
void		handle_dollar(char **str, char **result, t_env **env);

//Command Parsing
t_command	*new_command(void);
void		add_arg(t_command *cmd, char *word);
t_command	*parse_cmd(t_tokens *tokens);
void		redir_out(t_tokens **tokens, t_command *cmd);
void		redir_in_and_heredoc(t_tokens **tokens, t_command *cmd);
int			validate_syntax(t_tokens *tokens);

//command execution
void		execute_command(t_command *command, t_env **env);
void		execute_redir_out(t_command *cmd);
void		execute_redir_in(t_command *cmd);

//command utils misc
int			neg_pid(pid_t pid);
void		wait_pid(pid_t pid, pid_t last_pid, int status);
int			create_pipe(t_command *cmd, int pipe_fd[2]);
int			pipe_or_built_in(t_command *cmd, int *pipe_fd, t_env **env);

//built-ins
void		echo_builtin(char **argv);
int			cd_builtin(t_command *cmd, t_env **env);
void		env_bultin(t_env **env, char **envp);
void		export_built_in(t_command *cmd, t_env **env);
void		exit_builtin(t_command *cmd, t_env **env);

// built-in execution
void		get_current_dir(void);
int			execute_child_builtin(t_command *cmd, t_env **env);
int			exec_parent_built_in(t_command *cmd, t_env **env);
void		add_env_node(t_env **env, char *key, char *value);
void		print_env_list(t_env **env);
char		**env_to_array(t_env *env);
char		*get_env(char *str, t_env **env);
int			ft_strcmp(char *s1, char *s2);
void		unset_built_in(t_command *cmd, t_env	**env);
int			is_valid(char *str);
void		delete_node(t_env **head, char *key);

//built-in utils
int			check_cd_args(t_command *cmd);
int			check_cd_path(char *path, char *oldpwd);

//frees
void		clear_env_list(t_env **env);
void		free_array(char **array);
void		free_new(t_tokens *new);
void		free_tokens(t_tokens *tokens);
void		free_command(t_command *cmd);

//See where to place
int			empty_prompt(char *cmd);

//heredoc
void		add_heredoc(t_tokens *tokens, t_command *cmd);
int			init_heredoc(t_command *cmd);
void		dup_heredoc(t_command *cmd);

//path
char		*find_path(t_command *cmd, t_env **env);

#endif
