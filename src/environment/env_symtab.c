/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_symtab.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:06:53 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/14 16:52:47 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
// #include <stdio.h>
// # include <stdlib.h>

t_symtab	**init_env_symtab(char **environ)
{
	t_symtab	**symtab;
	t_symtab	*entry;
	int			i;

	symtab = malloc(sizeof(t_symtab *) * TABLE_SIZE);
	if (!symtab)
		perror("malloc failed");
	i = 0;
	while (i < TABLE_SIZE)
	{
		symtab[i] = NULL;
		i++;
	}
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
