#ifndef PARSING_H
# define PARSING_H

# include "tokenization.h"

//Parsing
int			class_command(char *cmd, char **envp);
void		add_token(t_tokens **tokens, t_tokens *new);
void		tokenization(t_tokens **tokens, char *cmd);
t_command	*start_lexer(char *cmd);

//Utils
int			is_space(char c);
int 		is_operator(char c);
int 		is_quote(char c);
int			which_token(char *cmd, int *i);
t_tokens	*tokenize_word(char *cmd, t_tokens *new, int *i);
void		tokenize_operator(char *cmd, t_tokens *new, int *i);
void		check_quotes(char *cmd, int *i);

//Expander (talvez criar um header proprio)
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
void		free_new(t_tokens *new);
void		free_tokens(t_tokens *tokens);
void        free_command(t_command *cmd);

// command execution
void	execute_command(t_command *command, char **envp);
void	execute_redir_out(t_command *cmd);
void	execute_redir_in(t_command *cmd);
void	child_process(t_command *cmd, int pipe_fd[2], int prev_fd, char **envp);
int	    create_pipe(t_command *cmd, int pipe_fd[2]);
//char	*find_path(char *word);
void	echo_builtin(char **argv);

#endif
