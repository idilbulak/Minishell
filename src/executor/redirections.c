#include "../../inc/filed.h"
#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	set_here_document(t_filed *fd, char *delimiter)
{
	char    buff[1];
	char    line[1024];
	int		i;

	i = 0;
	fd->redirect_in = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (read(STDIN_FILENO, buff, 1)) // replace 0 with fd->redirect_in for if input < ??
	{
		line[i] = buff[0];
		if (line[i] == '\n') {
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
	fd->redirect_in = open("tmp.txt", O_RDWR | O_CREAT, 0777);
	if (dup2(fd->redirect_in, STDIN_FILENO) == -1)
		perror("set_redirect_doubleless() failed");
	close(fd->redirect_in);
	unlink("tmp.txt");
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
		perror("set_redirect_less() failed");
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
			if (set_here_document(fd, list->next->word->word))
				return (1);
		list = list->next;
	}
	return (0);
}
