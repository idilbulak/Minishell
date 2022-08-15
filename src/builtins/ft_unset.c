/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:53:19 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/15 13:19:46 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	ft_unset(char **argv, t_symtab **symtab)
{
	if (ft_strchr(argv[1], '='))
	{
		printf("'%s': not a valid identifier\n", argv[1]);
		return (1);
	}
	else
		symtab_lookup(symtab, argv[1])->value = "";
		symtab_lookup(symtab, argv[1])->flag = 0;
	return (0);
}
