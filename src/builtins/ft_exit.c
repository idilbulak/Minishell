#include "../../inc/environment.h"
#include <stdlib.h>

static void    free_symtab(t_symtab **symtab)
{
	t_symtab	*tmp;
	int			i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		while(symtab[i])
		{
			tmp = symtab[i]->next;
			free(symtab[i]->name);
			free(symtab[i]->value);
			free(symtab[i]);
			symtab[i] = tmp;
		}
		i++;
	}
	free(symtab);
}

int	ft_exit(char **argv, t_symtab **symtab)
{
	(void)argv;
    free(argv);
    free_symtab(symtab);
	exit(EXIT_SUCCESS);
}
