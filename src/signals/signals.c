/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 17:32:59 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/12 17:33:00 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/signals.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("minishell$    ", 0);
		rl_redisplay();
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_code = 1;
	}
	if (sig == SIGQUIT)
	{
		rl_replace_line("minishell$    ", 0);
		rl_redisplay();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_code = 0;
	}
}

void	init_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}
