/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:52:44 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/16 13:39:27 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"

static int	invalid_name_identifier(char *name)
{
	int			i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=' && i > 0)
			break ;
		if (ft_isdigit(name[0])
			|| (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_'))
		{
			ft_putstr_fd("minishell: export:`", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	sort_list(t_symtab **list)
{
	int			i;
	t_symtab	*tmp;

	i = 0;
	while (list[i] && list[i + 1])
	{
		if (ft_strcmp(list[i]->name, list[i + 1]->name) > 0)
		{
			tmp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

static t_symtab	**create_export_variables_list(t_symtab **symtab)
{
	t_symtab	**list;
	t_symtab	*tmp;
	int			i;
	int			j;

	list = malloc(sizeof(t_symtab *) * (total_export_entries(symtab) + 1));
	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		tmp = symtab[i];
		while (tmp)
		{
			if (tmp->flag == FLAG_EXPORT)
			{
				list[j] = tmp;
				j++;
			}
			tmp = tmp->next;
		}
		i++;
	}
	list[j] = NULL;
	return (list);
}

static void	print_export_variables(t_symtab **symtab)
{
	t_symtab	**list;
	int			i;

	list = create_export_variables_list(symtab);
	sort_list(list);
	i = 0;
	while (list[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(list[i]->name, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(list[i]->value, 1);
		ft_putstr_fd("\"\n", 1);
		i++;
	}
	free(list);
}

int	ft_export(char **argv, t_symtab **symtab)
{
	t_symtab	*tmp;
	int			i;

	i = 0;
	if (!argv[1])
		print_export_variables(symtab);
	while (argv[++i])
	{
		if (invalid_name_identifier(argv[i]))
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
