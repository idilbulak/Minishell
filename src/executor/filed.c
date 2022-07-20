#include "../../inc/filed.h"
#include <stdio.h>
#include <stdlib.h>

void    reset_fd(t_filed *fd)
{
	if (dup2(fd->tmpin, STDIN_FILENO) == -1) {
		perror("dup2(3)");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd->tmpout, STDOUT_FILENO) == -1) {
		perror("dup2(4)");
		exit(EXIT_FAILURE);
	}
	close(fd->tmpin);
	close(fd->tmpout);
}

void	create_pipe(t_filed *fd)
{
	int		fdpipe[2];
	
	if (pipe(fdpipe) == -1) { 	
		perror("pipe()"); 		
		exit(EXIT_FAILURE);
	}
	fd->in = fdpipe[0]; // fdpipe[0] - read - input
	fd->out = fdpipe[1]; // fdpipe[1] - write -output
}

static int	is_final_cmd(t_word_list *list)
{
	while (list)
	{
		if (list->word->flags == TOKEN_PIPE)
			return (0);
		list = list->next;
	}
	return (1);
}

void	set_fd(t_word_list *list, t_filed *fd)
{
	check_redirections_in(list, fd);
	if (dup2(fd->in, STDIN_FILENO) == -1) {
		perror("set_fd dup2(1)");
		exit(EXIT_FAILURE);
	}
	close(fd->in);
	if (is_final_cmd(list))
		fd->out = dup(fd->tmpout);
	else
		create_pipe(fd);
	check_redirections_out(list, fd);
	if (dup2(fd->out, STDOUT_FILENO) == -1) {
		perror("set_fd dup2(2)");
		exit(EXIT_FAILURE);
	}
	close(fd->out);
}

void    init_fd(t_filed *fd)
{
	fd->tmpin = dup(STDIN_FILENO);
	fd->tmpout = dup(STDOUT_FILENO);
	fd->in = dup(STDIN_FILENO);
	fd->out = dup(STDOUT_FILENO);
}
