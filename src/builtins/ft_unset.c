/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:53:19 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/16 12:17:15 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <stdio.h>

static int	invalid_name_identifier(char *name)
{
	int			i;

	i = 0;
	while (name[i])
	{
		if (ft_isdigit(name[0])
			|| (!ft_isalpha(name[i]) && !ft_isdigit(name[i]) && name[i] != '_'))
		{
			ft_putstr_fd("minishell: unset:`", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **argv, t_symtab **symtab)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (invalid_name_identifier(argv[i]))
			continue ;
		else if (symtab_lookup(symtab, argv[i]))
			symtab_delete(symtab, argv[i]);
	}
	return (g_exit_code);
}

// int	ft_unset(char **argv, t_symtab **symtab)
// {
// 	int	i;

// 	i = 1;
// 	while (argv[i])
// 	{
// 		if (ft_strchr(argv[i], '='))
// 		{
// 			ft_putstr_fd("unset:`", 2);
// 			ft_putstr_fd(argv[i], 2);
// 			ft_putstr_fd("': not a valid identifier\n", 2);
// 			g_exit_code = 1;
// 		}
// 		else if (symtab_lookup(symtab, argv[i]))
// 			symtab_delete(symtab, argv[i]);
// 		i++;
// 	}
// 	return (g_exit_code);
// }