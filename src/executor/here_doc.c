/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 17:12:46 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/05 11:07:27 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/filed.h"
#include "../../inc/parser.h"
#include "../../inc/minishell.h"
#include <fcntl.h>

static void	sig_here_doc(int sig)
{
	(void)sig;
	unlink("tmp.txt");
	exit(EXIT_FAILURE);
}

static void	check_expension(char *str, t_symtab **symtab)
{
	t_word_list	word_list;
	
	word_list.word = str;
	word_list.flags = TOKEN_STRING;
	if (check_ifexpand(word_list) == 1)
			ft_expander(word_list, symtab);
	ft_split_quotes(word_list);
}

int	set_here_document(t_filed *fd, char *delimiter)
{
	char		*str;
	// t_word_list	*word_list;
	
	fd->redirect_in = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		dup2(fd->tmpin, STDIN_FILENO);
		dup2(fd->tmpout, STDOUT_FILENO);
		str = readline("> ");
		if (!str)
			exit(EXIT_FAILURE);
		if (ft_strcmp(str, delimiter) == 0)
			break ;
		write(fd->redirect_in, str, ft_strlen(str));
		write(fd->redirect_in, "\n", 1);
		free(str);
	}
	free(str);
	close(fd->redirect_in);
	fd->redirect_in = open("tmp.txt", O_RDWR | O_CREAT, 0777);
	dup2(fd->redirect_in, STDIN_FILENO);
	close(fd->redirect_in);
	exit(EXIT_SUCCESS);
}

int	init_here_document(t_filed *fd, char *delimiter)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_here_doc);
		set_here_document(fd, delimiter);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) == 1)
			return (1);
	fd->redirect_in = open("tmp.txt", O_RDWR | O_CREAT, 0777);
	dup2(fd->redirect_in, STDIN_FILENO);
	close(fd->redirect_in);
	unlink("tmp.txt");
	return (0);
}
