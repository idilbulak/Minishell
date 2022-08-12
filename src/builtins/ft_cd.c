/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:49:22 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/12 14:49:23 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include <unistd.h>

int	ft_cd(char **args, t_symtab **symtab)
{
	(void)symtab;
	if (chdir(args[1]) != 0)
	{
		perror(args[1]);
		return (1);
	}
	return (0);
}
