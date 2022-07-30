#include "../../inc/environment.h"

t_symtab    *new_entry(char *str) //malloc protection
{
	t_symtab    *new_entry;
	int         i;

	i = 0;
	new_entry = malloc(sizeof(t_symtab));
	while (str[i] != '=')
		i++;
	new_entry->name = ft_substr(str, 0, i);
	new_entry->value = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (new_entry);   
}

void    init_env_symtab(t_symtab **symtab)
{
	t_symtab    *entry;
	int         i;

	i = 0;
	while (environ[i])
	{
		entry = new_entry(environ[i]);
		entry->flag = FLAG_EXPORT;
		symtab_insert(symtab, entry);
		i++;        
	}
}

char    **create_env_array(t_symtab **symtab)
{
	char        **env;
	char        *str;
	t_symtab    *tmp;
	int         i;
	int         j;

	env = malloc(sizeof(char *) * total_env_entries(symtab) + 1);
	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		tmp = symtab[i];
		while (tmp)
		{
			if (tmp->flag == FLAG_EXPORT)
			{
				str = malloc(sizeof(char) * ft_strlen(tmp->name) + ft_strlen(tmp->value) + 2);
				ft_strlcpy(str, tmp->name, ft_strlen(tmp->name) + 1);
				ft_strlcpy(&str[ft_strlen(tmp->name)], "=", 2);
				ft_strlcpy(&str[ft_strlen(tmp->name) + 1], tmp->value, ft_strlen(tmp->value) + 1);
				env[j] = str;
				j++;
			}
			tmp = tmp->next;
		}
		i++;
	}
	env[j] = NULL;
	return (env);
}

int total_env_entries(t_symtab **symtab)
{
	t_symtab    *tmp;
	int         i;
	int         num;

	i = 0;
	num = 0;
	while (i < TABLE_SIZE)
	{
		tmp = symtab[i];
		while (tmp)
		{
			tmp = tmp->next;
			num++;
		}
		i++;
	}
	return (num);
}

void    delete_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
