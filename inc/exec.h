#ifndef EXEC_H
# define EXEC_H
# include <unistd.h>
# include <errno.h>
# include "parser.h"

typedef struct	s_child
{
	pid_t	pid;
	int		exit_code;
	int		status;
}				t_child;

int     executor(t_word_list *cmds);
int	    calc_num_args(t_word_list *list);
char	**create_args_array(t_word_list *list);
char    *search_path(char *cmd);
void	ft_error(int errornumber, char *errormessage);

# endif
