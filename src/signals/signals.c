#include "../../inc/signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
# include <sys/wait.h>

void	sig_handler(int sig)
{
	// write (1, "\b \b\b \b", 6);
// delete the previous buffer and give a prompt on new line
	if (sig == SIGINT)
	{
		rl_replace_line("minishell$    ", 0);
		rl_redisplay();
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
// does nothing, give just a prompt
	if (sig == SIGQUIT)
	{
		rl_replace_line("minishell$    ", 0);
		rl_redisplay();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	//ctrl-c
	signal(SIGINT, sig_handler);
	//ctrl-4
	signal(SIGQUIT, sig_handler);
}

/*
rl_clear_history: Clear the history list by deleting all of the entries, in the same manner as the History library's clear_history() function. 
				This differs from clear_history because it frees private data Readline saves in the history list.
rl_on_new_line : Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
rl_replace_line : Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. 
				If clear_undo is non-zero, the undo list associated with the current line is cleared.
rl_redisplay : Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
*/
