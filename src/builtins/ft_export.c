/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:52:44 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/23 14:00:06 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"

#include <stdio.h>

int	ft_export(char **argv, t_symtab **symtab)
{
	t_symtab	*tmp;
	int			i;

	i = 0;
	while (argv[++i])
	{
		tmp = new_entry(argv[i]);
		if (!tmp && !(symtab_lookup(symtab, argv[i])))
			continue;
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

// int	ft_export(char **argv, t_symtab **symtab)
// {
// 	t_symtab	*tmp;
// 	int			i;

// 	i = 1;
// 	while (argv[i])
// 	{
// 		tmp = new_entry(argv[i]);
// 		if (!tmp)
// 		{
// 			tmp = symtab_lookup(symtab, argv[i]);
// 			if (!tmp)
// 				return (0);
// 			tmp->flag = FLAG_EXPORT;
// 		}
// 		else if (!symtab_lookup(symtab, tmp->name))
// 		{
// 			tmp->flag = FLAG_EXPORT;
// 			symtab_insert(symtab, tmp);
// 		}
// 		else
// 		{
// 			symtab_delete(symtab, tmp->name);
// 			tmp->flag = FLAG_EXPORT;
// 			symtab_insert(symtab, tmp);
// 		}
// 		i++;
// 	}
// 	return (0);
// }