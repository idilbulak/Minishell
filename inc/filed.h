#ifndef FILE_D_H
# define FILE_D_H
# include "exec.h"

typedef struct	s_filed
{
	int		tmpin;
	int		tmpout;
	int		in;
	int		out;
}				t_filed;

void    init_fd(t_filed *fd);
void	set_fd(t_word_list *list, t_filed *fd);
void	create_pipe(t_filed *fd);
void    reset_fd(t_filed *fd);

void    read_till_delimiter(t_filed *fd, char *delimiter);
void    check_redirections_in(t_word_list *list, t_filed *fd);
void    check_redirections_out(t_word_list *list, t_filed *fd);

# endif