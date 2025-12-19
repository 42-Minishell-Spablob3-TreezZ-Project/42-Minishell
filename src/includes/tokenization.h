#ifndef TOKENIZATION_H
# define TOKENIZATION_H

typedef enum s_token_type
{
	TOKEN_WORD, 
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HERE_DOC,
	TOKEN_APPEND,
	
}	t_token_type;

typedef struct s_tokens
{
	t_token_type	type;
	char			*input;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}			t_tokens;

#endif
