/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:49:35 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/25 13:07:47 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/environment.h"
#include <stdio.h>

int	valid_flag(char *str)
{
	int	i;

	i = 2;
	if (str[1] && str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_echo(char **argv, t_symtab **symtab)
{
	int	i;
	int	mode;
	int	flag;

	(void)symtab;
	i = 1;
	mode = 0;
	flag = 0;
	while (argv[i])
	{
		if (mode == 0)
		{
			if (valid_flag(argv[i]))
				flag = 1;
			else
				mode = 1;
		}
		if (mode == 1)
			printf("%s ", argv[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}

// int	ft_echo(char **argv, t_symtab **symtab)
// {
// 	int	i;

// 	(void)symtab;
// 	i = 1;
// 	while (argv[i])
// 	{
// 		if (i == 1 && ft_strcmp(argv[1], "-n") == 0)
// 			i++;
// 		if (argv[i])
// 			printf("%s ", argv[i]);
// 		i++;
// 	}
// 	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
// 		return (0);
// 	printf("\n");
// 	return (0);
// }