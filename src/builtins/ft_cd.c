/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:49:22 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/23 14:00:06 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

// static void	set_oldpwd(t_symtab **symtab)
// {
// 	char	*cwd;
// 	char	*oldpwd;
	
// 	cwd = getcwd(NULL, 0);
// 	if (!symtab_lookup(symtab, "OLDPWD"))
// 	{
// 		oldpwd = ft_strjoin("OLDPWD=", cwd);
// 		if (!oldpwd)
// 			ft_error(EXIT_FAILURE, "malloc failed");
// 		symtab_insert(symtab, new_entry(oldpwd));
// 		symtab_lookup(symtab, "OLDPWD")->flag = FLAG_EXPORT;
// 		free(oldpwd);
// 		free(cwd);
// 	}
// 	else
// 	{
// 		free(symtab_lookup(symtab, "OLDPWD")->value);
// 		symtab_lookup(symtab, "OLDPWD")->value = cwd;
// 	}
// }

int	ft_cd(char **args, t_symtab **symtab)
{
	char	*cwd;
	
	// set_oldpwd(symtab);
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
