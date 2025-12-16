#ifndef TOKENIZATION_H
#define TOKENIZATION_H

typedf enum token_type
{
	TOKEN_WORD, 
	TOKEN_PIPE,
	TOKEN_REDIN,
	TOKEN_REDIROUT,
	TOKEN_HERE_DOC,
	
}	t_token_type,

typedef struct s_tokens
{
	char		*input;
	t_node_type	type;
	struct s_tokens *next;
}			t_tokens;