/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:52:44 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/23 15:28:37 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"

#include <stdio.h>

int	valid_name_indentifier(char *name)
{
	int			i;
	
	i = 0;
	while (name[i] != '=')
	{
		if (ft_isdigit(name[0])
		|| (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_'))
		{
			printf("export:'%s': not a valid identifier\n", name);
			return (0);
		}
		i++;	
	}
	return (1);
}

int	ft_export(char **argv, t_symtab **symtab)
{
	t_symtab	*tmp;
	int			i;

	i = 0;
	while (argv[++i])
	{
		if (!valid_name_indentifier(argv[i]))
			continue ;
		tmp = new_entry(argv[i]);
		if (!tmp && !(symtab_lookup(symtab, argv[i])))
			continue ;
		else if (!tmp && (symtab_lookup(symtab, argv[i])))
			symtab_lookup(symtab, argv[i])->flag = FLAG_EXPORT;
		else if (tmp)
		{
			if (symtab_lookup(symtab, tmp->name))
				symtab_delete(symtab, tmp->name);
			tmp->flag = FLAG_EXPORT;
			symtab_insert(symtab, tmp);	
		}
	}
	return (0);
}
