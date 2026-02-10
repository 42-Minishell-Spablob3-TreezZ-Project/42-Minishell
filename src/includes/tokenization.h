#ifndef TOKENIZATION_H
# define TOKENIZATION_H

typedef enum s_token_type
{
	TOKEN_WORD, 
	TOKEN_PIPE,
	TOKEN_REDIRIN,
	TOKEN_REDIROUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	
}	t_token_type;

typedef struct s_tokens
{
	t_token_type		type;
	char				*input;
	struct	s_tokens	*next;
	struct	s_tokens	*prev;
}				t_tokens;

// struct para os comandos
typedef struct s_command
{
	char				**argv; //argumentos do comando.
	char				*infile; // caso seja "<".
	char				*outfile; // caso seja ">" ou ">>".
	int					append; // flag para o append ">>".
	char				*heredoc_delimiter; // no caso de heredoc <<.
	int					heredoc_fd;
	struct s_command	*next;
}		t_command;

#endif
