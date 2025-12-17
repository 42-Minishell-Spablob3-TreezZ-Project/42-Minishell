#ifndef TOKENIZATION_H
#define TOKENIZATION_H

typedf enum token_type
{
	TOKEN_WORD, 
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HERE_DOC,
	TOKEN_APPEND,
	
}	t_token_type,

typedef struct s_tokens
{
	char		*input;
	t_node_type	type;
	struct s_tokens *next;
}			t_tokens;