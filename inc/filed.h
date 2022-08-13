#ifndef FILE_D_H
# define FILE_D_H
# include "exec.h"

typedef struct	s_filed
{
	int		tmpin;
	int		tmpout;
	int		redirect_in;
	int		in;
	int		out;
}				t_filed;

void    init_fd(t_filed *fd);
int		set_fd(t_word_list *list, t_filed *fd);//, t_child *child);
void	create_pipe(t_filed *fd);
void    reset_fd(t_filed *fd);

int		check_redirections(t_word_list *list, t_filed *fd);
int		set_input(t_word_list *list, t_filed *fd);
int		set_output(t_word_list *list, t_filed *fd);
int		set_append_output(t_word_list *list, t_filed *fd);
int		set_here_document(t_filed *fd, char *delimiter);

# endif