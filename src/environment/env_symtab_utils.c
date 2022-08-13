/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_symtab_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 11:54:25 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/13 11:59:58 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"

int	hash(char *name)
{
	int	i;
	int	len;
	int	hash_value;

	i = 0;
	hash_value = 0;
	len = ft_strlen(name);
	while (i < len)
	{
		hash_value += name[i];
		hash_value *= name[i];
		i++;
	}
	return (hash_value % TABLE_SIZE);
}

t_symtab	*new_entry(char *str)
{
	t_symtab	*new_entry;
	int			i;

	i = 0;
	new_entry = malloc(sizeof(t_symtab));
	if (!new_entry)
		return (NULL);
	while (str[i] != '=')
		i++;
	new_entry->name = ft_substr(str, 0, i);
	if (!new_entry->name)
		return (NULL);
	new_entry->value = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (!new_entry->value)
		return (NULL);
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
	while (tmp != NULL && ft_strncmp(tmp->name, name, ft_strlen(name)) != 0)
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
	while (tmp != NULL && ft_strncmp(tmp->name, name, ft_strlen(name)) != 0)
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
	free(tmp->value);
	free(tmp);
}