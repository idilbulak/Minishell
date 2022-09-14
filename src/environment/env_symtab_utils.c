/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_symtab_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 11:54:25 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/14 15:56:01 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	hash(char *name)
{
	unsigned int	hash_value;
	int				i;
	int				len;

	i = 0;
	hash_value = 0;
	len = ft_strlen(name);
	while (i < len)
	{
		hash_value += name[i];
		i++;
	}
	return (hash_value % TABLE_SIZE);
}

t_symtab	*new_entry(char *str)
{
	t_symtab	*new_entry;
	int			i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	new_entry = malloc(sizeof(t_symtab));
	if (!new_entry)
		return (NULL);
	new_entry->name = ft_substr(str, 0, i);
	new_entry->value = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	return (new_entry);
}

void	symtab_insert(t_symtab **symtab, t_symtab *entry)
{
	int	index;

	index = hash(entry->name);
	entry->next = symtab[index];
	symtab[index] = entry;
}

t_symtab	*symtab_lookup(t_symtab **symtab, char *name)
{
	int			index;
	t_symtab	*tmp;

	if (!name)
		return (NULL);
	index = hash(name);
	tmp = symtab[index];
	while (tmp != NULL && ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	return (tmp);
}

void	symtab_delete(t_symtab **symtab, char *name)
{
	int			index;
	t_symtab	*tmp;
	t_symtab	*prev;

	index = hash(name);
	tmp = symtab[index];
	prev = NULL;
	while (tmp != NULL && ft_strcmp(tmp->name, name) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	if (prev == NULL)
		symtab[index] = tmp->next;
	else
		prev->next = tmp->next;
	free(tmp->name);
	if (tmp->value != NULL)
		free(tmp->value);
	free(tmp);
}
