/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 17:32:59 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/30 13:43:21 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/signals.h"
#include "../../libft/libft.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 0;
	}
}

void	child_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3", 2);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
}

void	register_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	unregister_signals(void)
{
	signal(SIGINT, child_sig_handler);
	signal(SIGQUIT, child_sig_handler);
}
