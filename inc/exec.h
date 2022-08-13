#ifndef EXEC_H
# define EXEC_H
# include "environment.h"
# include <unistd.h>
# include <errno.h>
# include "parser.h"

typedef struct	s_child
{
	pid_t	pid;
	int		g_exit_code;
	int		status;
}				t_child;

int     executor(t_word_list *cmds, t_symtab **symtab);
int	    calc_num_args(t_word_list *list);
char	**create_args_array(t_word_list *list);
char    *search_path_var(char *cmd);
void	ft_error(int errornumber, char *errormessage);

# endif
