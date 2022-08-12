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

void	init_symtab(t_symtab **symtab)
{
	int	i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		symtab[i] = NULL;
		i++;
	}
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

t_symtab	*symtab_delete(t_symtab **symtab, char *name)
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
		return (NULL);
	if (prev == NULL)
		symtab[index] = tmp->next; // deleting the head
	else
		prev->next = tmp->next;
	return (tmp); // pointer to free in caller
}
