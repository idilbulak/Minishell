/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:52:44 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/25 19:14:38 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"

#include <stdio.h>

static int	invalid_name_indentifier(char *name)
{
	int			i;
	
	i = 0;
	while (name[i] && name[i] != '=')
	{
		if (ft_isdigit(name[0])
		|| (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_'))
		{
			
			ft_putstr_fd("export:'", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_code = 1;
			return (1);
		}
		i++;	
	}
	return (0);
}

// static int	invalid_option(char **argv)
// {
// 	int	i;

// 	i = 0;
// 	if (argv[1][0] == '-')
// 	{
// 		ft_putstr_fd("export:'", 2);
// 		while (argv[1][i] && argv[1][i] != '=')
// 			ft_putchar_fd(argv[1][i++], 2);
// 		ft_putstr_fd("': invalid option\n", 2);
// 		return (1);
// 	}
// 	return (0);
// }

static void	print_export_variables(t_symtab **symtab)
{
	t_symtab	*tmp;
	int			i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		tmp = symtab[i];
		while (tmp)
		{
			if (tmp->flag == FLAG_EXPORT)
			{
				ft_putstr_fd("declare -x ", 2);
				ft_putstr_fd(tmp->name, 2);
				ft_putstr_fd("=\"", 2);
				ft_putstr_fd(tmp->value, 2);
				ft_putstr_fd("\"\n", 2);
			}
			tmp = tmp->next;
		}
		i++;
	}
}

int	ft_export(char **argv, t_symtab **symtab)
{
	t_symtab	*tmp;
	int			i;

	i = 0;
	if (!argv[1])
		print_export_variables(symtab);
	// if (invalid_option(argv))
	// 	return (2);
	while (argv[++i])
	{
		if (invalid_name_indentifier(argv[i]))
			continue ;
		tmp = new_entry(argv[i]);
		if (!tmp && !(symtab_lookup(symtab, argv[i])))
			continue ;
		if (!tmp && (symtab_lookup(symtab, argv[i])))
			symtab_lookup(symtab, argv[i])->flag = FLAG_EXPORT;
		if (tmp)
		{
			if (symtab_lookup(symtab, tmp->name))
				symtab_delete(symtab, tmp->name);
			tmp->flag = FLAG_EXPORT;
			symtab_insert(symtab, tmp);	
		}
	}
	return (g_exit_code);
}
