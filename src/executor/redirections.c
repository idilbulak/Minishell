#include "../../inc/filed.h"
#include "../../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void    read_till_delimiter(t_filed *fd, char *delimiter)
{
	char    buff[1];
	char    line[1024];
	int		i;

	i = 0;
	fd->in = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (read(STDIN_FILENO, buff, 1)) // replace 0 with fd->in for if input < ??
	{
		line[i] = buff[0];
		if (line[i] == '\n') {
			line[i] = '\0';
			if (ft_strcmp(line, delimiter) == 0) //replace /w ft_strcmp!!
				break ;
			line[i] = '\n';
			write(fd->in, line, i + 1);
			i = -1;
		}
		i++;
	}
	close(fd->in);
	fd->in = open("tmp.txt", O_RDWR | O_CREAT, 0777);
	unlink("tmp.txt");
}

void    check_redirections_in(t_word_list *list, t_filed *fd)
{
	while (list && list->word->flags != TOKEN_PIPE)
	{
		if (list->word->flags == TOKEN_LESS) {
			close(fd->in);
			fd->in = open(list->next->word->word, O_RDONLY);
		}
		if (list->word->flags == TOKEN_DOUBLELESS) {
			close(fd->in);
			read_till_delimiter(fd, list->next->word->word); //make it child process??
		}
		if (fd->in == -1) {
			perror("open(1)");
			exit(EXIT_FAILURE);
		}
		list = list->next;
	}
}

void    check_redirections_out(t_word_list *list, t_filed *fd)
{
	while (list && list->word->flags != TOKEN_PIPE) 
	{
		if (list->word->flags == TOKEN_GREATER) {
			close(fd->out);
			fd->out = open(list->next->word->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (list->word->flags == TOKEN_DOUBLEGREATER) {
			close(fd->out);
			fd->out = open(list->next->word->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (fd->out == -1) {
			perror("open(2)");
			exit(EXIT_FAILURE);
		}
		list = list->next;
	}
}
