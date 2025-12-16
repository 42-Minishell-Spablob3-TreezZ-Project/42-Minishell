#ifndef MINISHELL_H
# define MINISHELL_H

//Standard Libraries
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>

// variavel global para os sinais
extern volatile sig_atomic_t g_sigint;

//Libft

# include "../../lib/libft/libft.h"

//Includes

# include "shell.h"
# include "parsing.h"

//Defines

#endif
