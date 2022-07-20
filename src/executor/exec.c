#include "libft.h"
#include "exec.h"
#include "builtins.h"
#include "filed.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

pid_t	do_execute(t_ast *ast, int i)
{
	char    *pathname;

	// close(fd->in); // necessary?
	pathname = ast->args[i]->data[0];
	if (!ft_strchr(pathname, '/'))
		pathname = search_path(ast->args[i]->data[0]);
	if (!pathname)
		return (0); //perror("command not found");
	execve(pathname, ast->args[i]->data, NULL);
	// perror("execve()");
	free(pathname);
	return (0); // exit(EXIT_FAILURE);
}

void    do_simple_command(t_ast *ast, t_child *child, int i)
{
	if (is_builtin(ast, child, i))
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
		do_execute(ast, i);
		if (errno == ENOENT)
			ft_exit(127, ast->args[i]->data[0]);
		else if (errno == EACCES)
			ft_exit(126, ast->args[i]->data[0]);
		else
			ft_exit(EXIT_FAILURE, "execve() failed");
	}
}

void	executor(t_ast *ast)
{
	t_filed	fd;
	t_child child;
	int		status;
	int		i = 0;
	int		num_cmd = 0;

	init_fd(&fd);
	while (ast->args[i])
	{
		if (ast->args[i] && ast->args[i]->type == TOKEN_STRING) 
		{
			set_fd(ast, &fd, i, num_cmd, ast->cmd_number);
			do_simple_command(ast, &child, i);
			num_cmd++;
		}
		i++;
	}
	if (waitpid(child.pid, &status, 0) == -1 && errno != ECHILD) 
	{
		perror("waitpid()");
		exit(EXIT_FAILURE);
	}
	reset_fd(&fd);
}
