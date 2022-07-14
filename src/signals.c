#include "../inc/signals.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// delete the previous buffer and give a prompt on new line
static void	sigint_handler(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 42);
	rl_redisplay();
}

// does nothing, give just a prompt
static void	sigquit_handler(int sig)
{
	rl_on_new_line();
	rl_redisplay();
}

void	init_signals(void)
{
	//ctrl-c
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	//ctrl-4
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
}

/*
rl_clear_history: Clear the history list by deleting all of the entries, in the same manner as the History library's clear_history() function. 
				This differs from clear_history because it frees private data Readline saves in the history list.
rl_on_new_line : Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
rl_replace_line : Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. 
				If clear_undo is non-zero, the undo list associated with the current line is cleared.
rl_redisplay : Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
*/
