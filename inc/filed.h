/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filed.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 18:17:46 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/08 10:11:09 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILED_H
# define FILED_H
# include "exec.h"

typedef struct s_filed
{
	int	tmpin;
	int	tmpout;
	int	redirect_in;
	int	in;
	int	out;
}		t_filed;

void	init_fd(t_filed *fd);
void	create_pipe(t_filed *fd);
void	reset_fd(t_filed *fd);
int		set_fd(t_word_list *list, t_filed *fd, t_symtab **symtab);

int		check_redirections(t_word_list *list, t_filed *fd, t_symtab **symtab);
int		set_input(t_word_list *list, t_filed *fd);
int		set_output(t_word_list *list, t_filed *fd);
int		set_append_output(t_word_list *list, t_filed *fd);
int		init_here_document(t_filed *fd, char *delimiter, t_symtab **symtab);
int		set_here_document(t_filed *fd, char *delimiter, t_symtab **symtab);

#endif