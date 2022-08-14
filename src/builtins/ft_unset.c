/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:53:19 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/14 18:12:03 by dsaat         ########   odam.nl         */
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
		symtab_delete(symtab, argv[1]);
	return (0);
}
