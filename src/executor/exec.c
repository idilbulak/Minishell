/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 13:13:21 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/14 15:27:37 by daansaat      ########   odam.nl         */
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

static void	execute_non_builtin(char **argv, t_symtab **symtab)
{
	char	**envp;
	char	*pathname;
	int		shlvl;
	int		i;

	pathname = argv[0];
	i = 0;
	if (!ft_strchr(pathname, '/'))
		pathname = search_path_var(argv[0], symtab, i);
	else if (argv[0][0] == '.' && argv[0][1] == '/')
		pathname = replace_dot_with_cwd(pathname + 1);
	if (!pathname)
		return ;
	if (ft_strcmp(argv[0], "./minishell") == 0)
	{
		shlvl = ft_atoi(symtab_lookup(symtab, "SHLVL")->value);
		shlvl += 1;
		free(symtab_lookup(symtab, "SHLVL")->value);
		symtab_lookup(symtab, "SHLVL")->value = ft_itoa(shlvl);
	}
	envp = create_env_array(symtab);
	execve(pathname, argv, envp);
}

static void	do_simple_command(char **argv, t_child *child, t_symtab **symtab,
							t_filed *fd)
{
	if (!argv[0])
		return ;
	if (symtab_lookup(symtab, "PIPESTATUS")->value[0] == '0'
		&& is_builtin(argv, symtab))
		return ;
	child->pid = fork();
	if (child->pid == -1)
		ft_error(-1, "fork failed");
	if (child->pid == 0)
	{
		close(fd->in);
		close(fd->tmpin);
		close(fd->tmpout);
		if (is_builtin(argv, symtab))
			exit(g_exit_code);
		else
			execute_non_builtin(argv, symtab);
		if (errno == ENOENT)
			ft_error(127, argv[0]);
		if (errno == EACCES)
			ft_error(126, argv[0]);
		else
			ft_error(EXIT_FAILURE, argv[0]);
	}
	else if (ft_strcmp(argv[0], "./minishell") == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);	
	}
}

void	executor(t_word_list *list, t_symtab **symtab)
{
	t_filed	fd;
	t_child	child;
	char	**argv;

	init_fd(&fd);
	set_pipeline_var(list, symtab);
	while (list)
	{
		if (set_fd(list, &fd, symtab) == 0)
		{
			argv = create_argv_array(list);
			do_simple_command(argv, &child, symtab, &fd);
			free(argv);
		}
		while (list->next && list->word->flags != TOKEN_PIPE)
			list = list->next;
		list = list->next;
	}
	reset_fd(&fd);
	wait_for_children(&child);
}
