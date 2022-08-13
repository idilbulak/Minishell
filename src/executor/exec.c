/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 13:13:21 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/13 12:50:21 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"
#include "../../inc/filed.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

static void	do_execute(char **args)
{
	char	*pathname;

	pathname = args[0];
	if (!ft_strchr(pathname, '/'))
		pathname = search_path_var(args[0]);
	if (!pathname)
		return ;
	execve(pathname, args, NULL);
	free(pathname);
}

static void	do_simple_command(char **args, t_child *child, t_symtab **symtab)
{
	if (!args[0])
		return ;
	if (is_builtin(args, child, symtab) != 0)
	{
		child->pid = fork();
		if (child->pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		if (child->pid == 0)
		{
			do_execute(args);
			if (errno == ENOENT)
				ft_error(127, args[0]);
			else if (errno == EACCES)
				ft_error(126, args[0]);
			else
				ft_error(EXIT_FAILURE, "execve() failed");
		}
	}
}

int	executor(t_word_list *list, t_symtab **symtab)
{
	t_filed	fd;
	t_child	child;
	char	**args;

	init_fd(&fd);
	while (list)
	{
		child.g_exit_code = 0;
		if (set_fd(list, &fd, &child) == 0)
		{
			args = create_args_array(list);
			do_simple_command(args, &child, symtab);
			free(args);
		}
		while (list->next && list->word->flags != TOKEN_PIPE)
			list = list->next;
		list = list->next;
	}
	if (waitpid(child.pid, &child.status, 0) > 0)
		if (WIFEXITED(child.status))
			child.g_exit_code = WEXITSTATUS(child.status);
	reset_fd(&fd);
	return (child.g_exit_code);
}
