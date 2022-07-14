#ifndef EXEC_H
# define EXEC_H

#include "parser.h"

typedef struct	s_filed
{
	int		tmpin;
	int		tmpout;
    int     redirect_out;
	int		in;
	int		out;
}	t_filed;

void	executor(t_ast *ast);

#endif