/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_symtab.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:06:53 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/23 14:58:18 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include <stdio.h>

t_symtab	**init_env_symtab(char **environ)
{
	t_symtab	**symtab;
	t_symtab	*entry;
	int			i;

	symtab = malloc(sizeof(t_symtab *) * TABLE_SIZE);
	if (!symtab)
		perror("malloc failed");
	// i = 0;
	// while (i < TABLE_SIZE) // needed???
	// {
	// 	symtab[i] = NULL;
	// 	i++;
	// }
	i = 0;
	while (environ[i])
	{
		entry = new_entry(environ[i]);
		entry->flag = FLAG_EXPORT;
		symtab_insert(symtab, entry);
		i++;
	}
	return (symtab);
}

// void	print_table(t_symtab **symtab)
// {
// 	int	        i;
// 	t_symtab    *tmp;

// 	i = 0;
// 	while (i < TABLE_SIZE)
// 	{
// 		if (symtab[i] == NULL)
// 			printf("%d\t------\n", i);
// 		else
// 		{
// 			tmp = symtab[i];
// 			printf("%d\t", i);
// 			while (tmp != NULL)
// 			{
// 				printf("%s:%s || ", tmp->name, tmp->value);
// 				tmp = tmp->next;
// 			}
// 			printf("\n");
// 		}
// 		i++;
// 	}
// }
