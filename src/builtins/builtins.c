/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:48:21 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/09 12:55:49 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/builtins.h"

int	is_builtin(char **args, t_symtab **symtab)
{
	if (ft_strcmp(args[0], "cd") == 0)
		g_exit_code = ft_cd(args, symtab);
	else if (ft_strcmp(args[0], "echo") == 0)
		g_exit_code = ft_echo(args, symtab);
	else if (ft_strcmp(args[0], "env") == 0)
		g_exit_code = ft_env(args, symtab);
	else if (ft_strcmp(args[0], "exit") == 0)
		g_exit_code = ft_exit(args, symtab);
	else if (ft_strcmp(args[0], "export") == 0)
		g_exit_code = ft_export(args, symtab);
	else if (ft_strcmp(args[0], "pwd") == 0)
		g_exit_code = ft_pwd(args, symtab);
	else if (ft_strcmp(args[0], "unset") == 0)
		g_exit_code = ft_unset(args, symtab);
	else
		return (0);
	return (1);
}
