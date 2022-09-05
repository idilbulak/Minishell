/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filed.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 17:09:38 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/05 11:42:57 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/filed.h"
#include "../../inc/environment.h"

void	init_fd(t_filed *fd)
{
	fd->tmpin = dup(STDIN_FILENO);
	fd->tmpout = dup(STDOUT_FILENO);
	fd->in = dup(STDIN_FILENO);
}

void	create_pipe(t_filed *fd)
{
	int		fdpipe[2];

	if (pipe(fdpipe) == -1)
		ft_error(EXIT_FAILURE, "pipe failed");
	fd->in = fdpipe[0];
	fd->out = fdpipe[1];
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

int	set_fd(t_word_list *list, t_filed *fd, t_symtab **symtab)
{
	if (dup2(fd->in, STDIN_FILENO) == -1)
		ft_error(EXIT_FAILURE, "dup2 failed");
	close(fd->in);
	if (is_final_cmd(list))
		fd->out = dup(fd->tmpout);
	else
		create_pipe(fd);
	if (check_redirections(list, fd, symtab) != 0)
	{
		close(fd->out);
		g_exit_code = 1;
		return (1);
	}
	if (dup2(fd->out, STDOUT_FILENO) == -1)
		ft_error(EXIT_FAILURE, "dup2 failed");
	close(fd->out);
	return (0);
}

void	reset_fd(t_filed *fd)
{
	if (dup2(fd->tmpin, STDIN_FILENO) == -1)
		ft_error(EXIT_FAILURE, "dup2 failed");
	if (dup2(fd->tmpout, STDOUT_FILENO) == -1)
		ft_error(EXIT_FAILURE, "dup2 failed");
	close(fd->tmpin);
	close(fd->tmpout);
}
