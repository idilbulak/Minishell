/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 17:11:52 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/05 11:43:19 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/filed.h"
#include "../../inc/parser.h"
#include "../../inc/minishell.h"
#include <fcntl.h>

int	set_input(t_word_list *list, t_filed *fd)
{
	fd->redirect_in = open(list->next->word->word, O_RDONLY);
	if (fd->redirect_in == -1)
	{
		perror(list->next->word->word);
		return (1);
	}
	if (dup2(fd->redirect_in, STDIN_FILENO) == -1)
		ft_error(EXIT_FAILURE, "dup2 failed");
	close(fd->redirect_in);
	return (0);
}

int	set_output(t_word_list *list, t_filed *fd)
{
	close(fd->out);
	fd->out = open(list->next->word->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd->out == -1)
	{
		perror(list->next->word->word);
		return (1);
	}
	return (0);
}

int	set_append_output(t_word_list *list, t_filed *fd)
{
	close(fd->out);
	fd->out = open(list->next->word->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd->out == -1)
	{
		perror(list->next->word->word);
		return (1);
	}
	return (0);
}

int	check_redirections(t_word_list *list, t_filed *fd, t_symtab **symtab)
{	
	while (list && list->word->flags != TOKEN_PIPE)
	{
		if (list->word->flags == TOKEN_LESS)
			if (set_input(list, fd))
				return (1);
		if (list->word->flags == TOKEN_GREATER)
			if (set_output(list, fd))
				return (1);
		if (list->word->flags == TOKEN_DOUBLEGREATER)
			if (set_append_output(list, fd))
				return (1);
		if (list->word->flags == TOKEN_DOUBLELESS)
			if (init_here_document(fd, list->next->word->word, symtab))
				return (1);
		list = list->next;
	}
	return (0);
}
