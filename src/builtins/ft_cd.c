/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:49:22 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/14 15:56:06 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

int	ft_cd(char **args, t_symtab **symtab)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!symtab_lookup(symtab, "OLDPWD"))
		symtab_insert(symtab, new_entry("OLDPWD="));
	free(symtab_lookup(symtab, "OLDPWD")->value);
	symtab_lookup(symtab, "OLDPWD")->value = cwd;	
	if (args[1] && chdir(args[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(args[1]);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	free(symtab_lookup(symtab, "PWD")->value);
	symtab_lookup(symtab, "PWD")->value = cwd;
	return (0);
}
