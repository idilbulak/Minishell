#ifndef SIGNALS_H
# define SIGNALS_H

#include <readline/readline.h>
#include <signal.h>

void		init_signals(void);
void	prompt(void);

void	rl_replace_line (const char *text, int clear_undo);
#endif
