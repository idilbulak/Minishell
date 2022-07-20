#ifndef EXEC_H
# define EXEC_H
# include <unistd.h>
# include <errno.h>
# include "parser.h"

typedef struct	s_child
{
	pid_t	pid;
	int		return_status;
	int		state;
}				t_child;

void	executor(t_word_list *cmds);
char    *search_path(char *cmd);

# endif
