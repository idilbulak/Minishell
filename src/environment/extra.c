/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 16:40:25 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/13 16:40:26 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
// 	init_env_symtab(symtab);
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