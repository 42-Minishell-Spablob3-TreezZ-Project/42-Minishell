/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:55:49 by joapedro          #+#    #+#             */
/*   Updated: 2026/02/19 11:55:51 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/wait.h>

// variavel global para os sinais
extern int g_exit_status;

//Libft

# include "../../lib/libft/libft.h"

//Includes

# include "shell.h"
# include "parsing.h"
# include "tokenization.h"

//Defines

#endif
