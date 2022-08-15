/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 13:13:21 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/15 14:55:27 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"
#include "../../inc/filed.h"
#include <errno.h>

void	ft_error(int exit_code, char *error_message)
{
	g_exit_code = exit_code;
	perror(error_message);
	exit(g_exit_code);
}

static void	do_execute(char **args, t_symtab **symtab)
{
	char	**envp;
	char	*pathname;

	pathname = args[0];
	if (!ft_strchr(pathname, '/'))
		pathname = search_path_var(args[0], symtab);
	if (!pathname)
		return ;
	envp = create_env_array(symtab);
	execve(pathname, args, envp);
}

static void	do_simple_command(char **args, t_child *child, t_symtab **symtab)
{

	if (!args[0])
		return ;
	if (is_builtin(args, symtab) == 0)
		return ;
	child->pid = fork();
	if (child->pid == -1)
		ft_error(EXIT_FAILURE, "fork failed");
	if (child->pid == 0)
	{
		do_execute(args, symtab);
		if (errno == ENOENT)
			ft_error(127, args[0]);
		if (errno == EACCES)
			ft_error(126, args[0]);
		else
			ft_error(EXIT_FAILURE, "execve failed");
	}
}

void	executor(t_word_list *list, t_symtab **symtab)
{
	t_filed	fd;
	t_child	child;
	char	**args;

	init_fd(&fd);
	while (list)
	{
		if (set_fd(list, &fd) == 0)
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
		if (WIFEXITED(child.status) || WIFSIGNALED(child.status))
			g_exit_code = WEXITSTATUS(child.status);
	// while (!WIFEXITED(child.status) && !WIFSIGNALED(child.status))
	// 	waitpid(0, &child.status, 0);
	reset_fd(&fd);
}
