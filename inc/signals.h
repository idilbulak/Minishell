#ifndef SIGNALS_H
# define SIGNALS_H

#include <readline/readline.h>
#include <signal.h>

static void	sigint_handler(int sig);
static void	sigquit_handler(int sig);
void		init_signals(void);

#endif
