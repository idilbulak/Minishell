/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 18:10:30 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/23 14:00:06 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "environment.h"

typedef struct s_builtins
{
	char	*name;
	int		(*funct)(char **argv, t_symtab **symtab);
}			t_builtins;

void	init_builtins(t_builtins *builtins);
int		is_builtin(char **args, t_symtab **symtab);
int		ft_echo(char **argv, t_symtab **symtab);
int		ft_cd(char **argv, t_symtab **symtab);
int		ft_pwd(char **argv, t_symtab **symtab);
int		ft_export(char **argv, t_symtab **symtab);
int		ft_unset(char **argv, t_symtab **symtab);
int		ft_env(char **argv, t_symtab **symtab);
int		ft_exit(char **argv, t_symtab **symtab);

#endif
