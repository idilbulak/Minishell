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
	int	status;
	
	(void)argv;
	status = 0;
	if (argv[1])
		status = ft_atoi(argv[1]);
    free(argv);
    free_symtab(symtab);
	exit(status);
}
