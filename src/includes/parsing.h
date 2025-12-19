#ifndef PARSING_H
# define PARSING_H

# include "tokenization.h"

//Parsing
int			class_command(char *cmd);
void		add_token(t_tokens **tokens, t_tokens *new);
void		start_lexer(t_tokens **tokens, char *cmd);
char		*parse_command(char *cmd);

//Utils
int			is_space(char c);
int 		is_operator(char c);
int 		is_quote(char c);
int			which_token(char *cmd, int *i);
t_tokens	*tokenize_word(char *cmd, t_tokens *new, int *i);
t_tokens	*tokenize_operator(char *cmd, t_tokens *new, int *i);
void		check_quotes(char *cmd, int *i);

#endif
