/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 13:13:21 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/05 10:58:26 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/builtins.h"
#include "../../inc/filed.h"
#include "../../inc/environment.h"
#include <errno.h>

static void	set_pipeline_var(t_word_list *list, t_symtab **symtab)
{
	t_symtab	*entry;

	if (symtab_lookup(symtab, "PIPESTATUS"))
		symtab_delete(symtab, "PIPESTATUS");
	entry = new_entry("PIPESTATUS=0");
	symtab_insert(symtab, entry);
	while (list)
	{
		if (list->word->flags == TOKEN_PIPE)
			symtab_lookup(symtab, "PIPESTATUS")->value[0] = '1';
		list = list->next;
	}
}

static void	wait_for_children(t_child *child)
{
	if (waitpid(child->pid, &child->status, 0) > 0)
	{
		if (WIFEXITED(child->status))
			g_exit_code = WEXITSTATUS(child->status);
		else if (WIFSIGNALED(child->status))
			g_exit_code = WTERMSIG(child->status) + 128;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}

static void	execute_non_builtin(char **args, t_symtab **symtab)
{
	char	**envp;
	char	*pathname;

	pathname = args[0];
	if (!ft_strchr(pathname, '/'))
		pathname = search_path_var(args[0], symtab);
	else if (args[0][0] == '.' && args[0][1] == '/')
		pathname = replace_dot_with_cwd(pathname + 1);
	if (!pathname)
		return ;
	envp = create_env_array(symtab);
	execve(pathname, args, envp);
}

static void	do_simple_command(char **args, t_child *child, t_symtab **symtab,
							t_filed *fd)
{
	if (!args[0])
		return ;
	if (symtab_lookup(symtab, "PIPESTATUS")->value[0] == '0'
		&& is_builtin(args, symtab))
		return ;
	child->pid = fork();
	if (child->pid == -1)
		ft_error(-1, "fork failed");//ft_error(EXIT_FAILURE, "fork failed");
	if (child->pid == 0)
	{
		close(fd->in);
		if (is_builtin(args, symtab))
			exit(g_exit_code);
		else
			execute_non_builtin(args, symtab);
		if (errno == ENOENT)
			ft_error(127, args[0]);
		if (errno == EACCES)
			ft_error(126, args[0]);
		else
			ft_error(EXIT_FAILURE, args[0]);
	}
}

void	executor(t_word_list *list, t_symtab **symtab)
{
	t_filed	fd;
	t_child	child;
	char	**args;

	init_fd(&fd);
	set_pipeline_var(list, symtab);
	while (list && g_exit_code != -1) //
	{
		if (set_fd(list, &fd) == 0)
		{
			args = create_args_array(list);
			do_simple_command(args, &child, symtab, &fd);
			free(args);
		}
		while (list->next && list->word->flags != TOKEN_PIPE)
			list = list->next;
		list = list->next;
	}
	reset_fd(&fd);
	wait_for_children(&child);
}
