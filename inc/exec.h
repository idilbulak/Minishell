#ifndef EXEC_H
# define EXEC_H
# include "environment.h"
# include <unistd.h>
# include <errno.h>
# include "parser.h"

typedef struct	s_child
{
	pid_t	pid;
	int		status;
}				t_child;

void	executor(t_word_list *cmds, t_symtab **symtab);
char	**create_args_array(t_word_list *list);
char    *search_path_var(char *cmd);
void	ft_error(int errornumber, char *errormessage);

# endif
