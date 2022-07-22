#include "../../libft/libft.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"
#include "../../inc/filed.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

void	do_execute(char **args)
{
	char    *pathname;

	// close(fd->in); // necessary?
	pathname = args[0];
	if (!ft_strchr(pathname, '/'))
		pathname = search_path(args[0]);
	if (!pathname)
		return ;//(0); //perror("command not found");
	execve(pathname, args, NULL);
	// perror("execve()");
	free(pathname);
	// return (0); // exit(EXIT_FAILURE);
}

void    do_simple_command(char **args, t_child *child)
{
	if (is_builtin(args, child))
		return ;
	else
	child->pid = fork();
	if (child->pid == -1) 
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (child->pid == 0)
	{
		do_execute(args);
		printf("6\n");
		if (errno == ENOENT)
			ft_error(127, args[0]);
		else if (errno == EACCES)
			ft_error(126, args[0]);
		else
			ft_error(EXIT_FAILURE, "execve() failed");
	}
}

int	executor(t_word_list *list)
{
	t_filed	fd;
	t_child child;
	char    **args;

	init_fd(&fd);
	while (list)
	{
		child.exit_code = 0;
		if (set_fd(list, &fd, &child) == 0)
		{
			args = create_args_array(list);
			do_simple_command(args, &child);
			free(args);
		}
		while (list->next && list->word->flags != TOKEN_PIPE)
			list = list->next;
		list = list->next;
	}
	if (waitpid(child.pid, &child.status, 0) == -1 && errno != ECHILD) 
		ft_error(EXIT_FAILURE, "waitpid() failed");
	if (WIFEXITED(child.status))
		child.exit_code = WEXITSTATUS(child.status);
	reset_fd(&fd);
	return(child.exit_code);
}