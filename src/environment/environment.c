#include "../../inc/environment.h"

void    init_env(t_symtab **symtab)
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

t_symtab    *new_entry(char *str)
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

int num_total_entry(t_symtab **symtab)
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

char    **create_env_array(t_symtab **symtab)
{
	char        **env;
	char        *str;
	t_symtab    *tmp;
	int         i;
	int         j;

	env = malloc(sizeof(char *) * num_total_entry(symtab) + 1);
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
	return (env);
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

// int main(void)
// {
// 	t_symtab	**symtab;
// 	char        **env;

// 	symtab = malloc(sizeof(t_symtab *) * TABLE_SIZE);
// 	init_symtab(symtab);
// 	init_env(symtab);
// 	env = create_env_array(symtab);

// 	int i = 0;
// 	while (env[i])
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// 	// printf("%d\n", num_total_entry(sym_table));
// 	// print_table(sym_table);

// 	// t_symtab	*tmp;
// 	// tmp = sym_table_lookup(sym_table, "USER");
// 	// if (!tmp)
// 	//     printf("no entry\n");
// 	// else
// 	//     printf("%s\n", tmp->value);
// }