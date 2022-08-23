/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:49:35 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/23 14:00:06 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/environment.h"
#include <stdio.h>

int	ft_echo(char **argv, t_symtab **symtab)
{
	int	i;

	(void)symtab;
	i = 1;
	while (argv[i])
	{
		if (i == 1 && ft_strcmp(argv[1], "-n") == 0)
			i++;
		if (argv[i])
			printf("%s ", argv[i]);
		i++;
	}
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
		return (0);
	printf("\n");
	return (0);
}
