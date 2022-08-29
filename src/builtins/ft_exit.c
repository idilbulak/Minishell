/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:51:58 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/29 11:57:02 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_exit(char **argv, t_symtab **symtab)
{
	int	i;

	(void)symtab;
	ft_putstr_fd("exit\n", 1);
	if (argv[1])
	{
		i = 0;
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(argv[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
			i++;
		}
		exit(ft_atoi(argv[1]));
	}
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	exit(EXIT_SUCCESS);
}
