/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 13:13:21 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/26 10:12:22 by daansaat      ########   odam.nl         */
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

static void	do_simple_command(char **args, t_child *child, t_symtab **symtab, t_filed *fd)
{

	if (!args[0])
		return ;
	if (!child->is_pipeline && is_builtin(args, symtab))
		return ;
	child->pid = fork();
	if (child->pid == -1)
		ft_error(EXIT_FAILURE, "fork failed");
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
			ft_error(EXIT_FAILURE, args[0]);//"execve failed");
	}
}

static int	check_if_pipeline(t_word_list *list)
{
	while (list)
	{
		if (list->word->flags == TOKEN_PIPE)
			return (1);
		list = list->next;
	}
	return (0);
}

void	executor(t_word_list *list, t_symtab **symtab)
{
	t_filed	fd;
	t_child	child;
	char	**args;

	init_fd(&fd);
	child.is_pipeline = check_if_pipeline(list);
	while (list)
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
	// {
	if (waitpid(child.pid, &child.status, 0) > 0)
	{
		if (WIFEXITED(child.status))// || WIFSIGNALED(child.status))
			g_exit_code = WEXITSTATUS(child.status);
		else if (WIFSIGNALED(child.status))
			g_exit_code = WTERMSIG(child.status) + 128;	
	}
	// }
	// while (!WIFEXITED(child.status) && !WIFSIGNALED(child.status))
	while (waitpid(-1, &child.status, 0) > 0)
		;
	// 	waitpid(0, &child.status, 0);
	// printf("%d\n", g_exit_code);
}
