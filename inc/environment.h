/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 18:16:23 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/14 13:12:06 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>

# define TABLE_SIZE 25
# define FLAG_EXPORT 1

int	g_exit_code;

typedef struct s_symtab
{
	char			*name;
	char			*value;
	int				flag;
	struct s_symtab	*next;
}					t_symtab;

int			hash(char *name);
void		symtab_insert(t_symtab **symtab, t_symtab *entry);
void		symtab_delete(t_symtab **symtab, char *name);
t_symtab	*symtab_lookup(t_symtab **symtab, char *name);
t_symtab	*new_entry(char *str);
t_symtab	**init_env_symtab(char **environ);

int			total_export_entries(t_symtab **symtab);
char		**create_env_array(t_symtab **symtab);
void		delete_env_array(char **env);

void		ft_error(int errornumber, char *errormessage);

#endif
