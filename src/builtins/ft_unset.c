/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:53:19 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/29 10:20:26 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	ft_unset(char **argv, t_symtab **symtab)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			ft_putstr_fd("unset:'", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exit_code = 1;
		}
		else if (symtab_lookup(symtab, argv[i]))
			symtab_delete(symtab, argv[i]);
		i++;
	}
	return (g_exit_code);
}
