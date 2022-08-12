/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 17:12:14 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/12 17:32:52 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>

void	sig_handler(int sig);
void	init_signals(void);
void	rl_replace_line(const char *text, int clear_undo);

#endif
