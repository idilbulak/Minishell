/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:53:04 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/16 10:28:32 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include <stdio.h>
#include <unistd.h>

int	ft_pwd(char **argv, t_symtab **symtab)
{
	char	*cwd;

	(void)symtab;
	(void)argv;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
