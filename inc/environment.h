#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>

# define TABLE_SIZE 25
# define FLAG_EXPORT 1

extern char   **environ;

typedef struct	s_symtab
{
	char			*name;
	char			*value;
	int				flag;
	struct s_symtab	*next;
}				t_symtab;

int	        hash(char *name);
void	    init_symtab(t_symtab **symtab);
void	    symtab_insert(t_symtab **symtab, t_symtab *entry);
t_symtab	*symtab_lookup(t_symtab **symtab, char *name);
t_symtab	*symtab_delete(t_symtab **symtab, char *name);

void        init_env(t_symtab **symtab);
int         num_total_entry(t_symtab **symtab);
char        **create_env_array(t_symtab **symtab);
t_symtab    *new_entry(char *str);

# endif