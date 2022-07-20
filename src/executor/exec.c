#include "../../libft/libft.h"
#include "../../inc/exec.h"
#include "../../inc/builtins.h"
#include "../../inc/filed.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

pid_t	do_execute(char **args)
{
	char    *pathname;

	// close(fd->in); // necessary?
	pathname = args[0];
	if (!ft_strchr(pathname, '/'))
		pathname = search_path(args[0]);
	if (!pathname)
		return (0); //perror("command not found");
	execve(pathname, args, NULL);
	// perror("execve()");
	free(pathname);
	return (0); // exit(EXIT_FAILURE);
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
		if (errno == ENOENT)
			ft_exit(127, args[0]);
		else if (errno == EACCES)
			ft_exit(126, args[0]);
		else
			ft_exit(EXIT_FAILURE, "execve() failed");
	}
}

static char	**set_args(t_word_list **list)
{
	t_word_list *tmp;
	char		**args;
	int			i;

	i = 0;
	tmp = *list;
    args = malloc(sizeof(char*) * 255);
	while (tmp && tmp->word->flags != TOKEN_PIPE)
	{
		if (tmp->word->flags == TOKEN_STRING)
		{
			args[i] = malloc(sizeof(char) * ft_strlen(tmp->word->word) + 1);
			ft_strlcpy(args[i], tmp->word->word, ft_strlen(tmp->word->word) + 1);
			i++;
		}
		else if (tmp->word->flags != TOKEN_STRING)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	args[i] = NULL;
	if (tmp->word->flags == TOKEN_PIPE)
		tmp = tmp->next;
	*list = tmp;
	return (args);

}

void	executor(t_word_list *list)
{
	t_filed	fd;
	t_child child;
    char    **args;
	int		status;

	init_fd(&fd);
	while (list)//ast->args[i])
	{
		set_fd(list, &fd);
        args = set_args(&list);
		do_simple_command(args, &child);
		free(args);
        // if (ast->args[i] && ast->args[i]->type == TOKEN_STRING) 
		// {
		// 	set_fd(ast, &fd, i, num_cmd, ast->cmd_number);
		// 	do_simple_command(ast, &child, i);
		// 	num_cmd++;
		// }
		// i++;
	}
	if (waitpid(child.pid, &status, 0) == -1 && errno != ECHILD) 
	{
		perror("waitpid()");
		exit(EXIT_FAILURE);
	}
	reset_fd(&fd);
}
