#ifndef ENV_H
# define ENV_H

#include <stdbool.h>
#include "parser.h"

typedef struct s_dirs
{
	char			*name;
	char			*value;
	struct s_dirs	*next;
}	t_dirs;

typedef struct	s_env
{
	t_dirs			*dir_list;
	bool			if_forked;
	bool			if_exit_status;
}	t_env;

void	init_env(char **env);

#endif