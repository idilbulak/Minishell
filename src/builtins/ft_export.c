#include "../../inc/environment.h"

int	ft_export(char **argv, t_symtab **symtab)
{
	t_symtab	*tmp;
	
	if (!ft_strchr(argv[1], '='))
	{
		tmp = symtab_lookup(symtab, argv[1]);
		if (!tmp)
			return (0);
		tmp->flag = FLAG_EXPORT;
	}
	else
	{
		tmp = new_entry(argv[1]);
		tmp->flag = FLAG_EXPORT;
		symtab_insert(symtab, tmp);
	}
	return (0);
}
