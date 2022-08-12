/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:06:53 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/12 16:31:27 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"

t_symtab	*new_entry(char *str) //malloc protection
{
	t_symtab	*new_entry;
	int			i;

	i = 0;
	new_entry = malloc(sizeof(t_symtab));
	while (str[i] != '=')
		i++;
	new_entry->name = ft_substr(str, 0, i);
	new_entry->value = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (new_entry);
}

void	init_env_symtab(t_symtab **symtab, char **environ)
{
	t_symtab	*entry;
	int			i;

	i = 0;
	while (environ[i])
	{
		entry = new_entry(environ[i]);
		entry->flag = FLAG_EXPORT;
		symtab_insert(symtab, entry);
		i++;
	}
}
