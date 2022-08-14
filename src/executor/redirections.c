/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 17:11:52 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/14 10:16:36 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/filed.h"
#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	set_here_document(t_filed *fd, char *delimiter)
{
	char	buff[1];
	char	line[1024];
	int		i;

	i = 0;
	fd->redirect_in = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (read(STDIN_FILENO, buff, 1))
	{
		line[i] = buff[0];
		if (line[i] == '\n')
		{
			line[i] = '\0';
			if (ft_strcmp(line, delimiter) == 0)
				break ;
			line[i] = '\n';
			write(fd->redirect_in, line, i + 1);
			i = -1;
		}
		i++;
	}
	close(fd->redirect_in);
	return (0);
}

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

int	check_redirections(t_word_list *list, t_filed *fd)
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
		{
			set_here_document(fd, list->next->word->word);
			fd->redirect_in = open("tmp.txt", O_RDWR | O_CREAT, 0777);
			dup2(fd->redirect_in, STDIN_FILENO);
			close(fd->redirect_in);
			unlink("tmp.txt");
		}
		list = list->next;
	}
	return (0);
}
