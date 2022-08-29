/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:49:22 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/29 10:26:05 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

int	ft_cd(char **args, t_symtab **symtab)
{
	char	*cwd;

	if (chdir(args[1]) != 0)
	{
		perror(args[1]);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	free(symtab_lookup(symtab, "PWD")->value);
	symtab_lookup(symtab, "PWD")->value = cwd;
	return (0);
}
