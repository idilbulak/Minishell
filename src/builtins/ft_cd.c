/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:49:22 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/16 09:51:49 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

static void	set_pwd(t_symtab **symtab, char *cwd, char *pwd)
{
	if (!symtab_lookup(symtab, "OLDPWD"))
		symtab_insert(symtab, new_entry("OLDPWD="));
	free(symtab_lookup(symtab, pwd)->value);
	symtab_lookup(symtab, pwd)->value = cwd;
}

int	ft_cd(char **args, t_symtab **symtab)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("minishell: cd: getcwd");
	else
		set_pwd(symtab, cwd, "OLDPWD");
	if (args[1] && chdir(args[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(args[1]);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("minishell: cd: getcwd");
	else
		set_pwd(symtab, cwd, "PWD");
	return (0);
}
