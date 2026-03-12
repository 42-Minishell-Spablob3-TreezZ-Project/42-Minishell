/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joapedro <joapedro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:56:04 by joapedro          #+#    #+#             */
/*   Updated: 2026/03/12 15:28:16 by joapedro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

void	start_shell(char **envp);
char	*create_prompt(void);
int		handle_signals(void);
void	block_signal(void);

#endif
