/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:53:19 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/12 14:53:20 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"

int	ft_unset(char **argv, t_symtab **symtab)
{
	t_symtab	*tmp;

	if (ft_strchr(argv[1], '='))
	{
		printf("'%s': not a valid identifier\n", argv[1]);
		return (1);
	}
	else
	{
		tmp = symtab_lookup(symtab, argv[1]);
		if (!tmp)
			return (0);
		tmp = symtab_delete(symtab, argv[1]);
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	return (0);
}
