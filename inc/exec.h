/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 18:17:15 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/13 18:17:16 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "environment.h"
# include <unistd.h>
# include <errno.h>
# include "parser.h"

typedef struct s_child
{
	pid_t	pid;
	int		status;
}			t_child;

void	executor(t_word_list *cmds, t_symtab **symtab);
char	**create_args_array(t_word_list *list);
char	*search_path_var(char *cmd);

#endif
