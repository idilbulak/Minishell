/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 18:10:30 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/09 12:55:38 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "environment.h"

int		is_builtin(char **args, t_symtab **symtab);
int		ft_echo(char **argv, t_symtab **symtab);
int		ft_cd(char **argv, t_symtab **symtab);
int		ft_pwd(char **argv, t_symtab **symtab);
int		ft_export(char **argv, t_symtab **symtab);
int		ft_unset(char **argv, t_symtab **symtab);
int		ft_env(char **argv, t_symtab **symtab);
int		ft_exit(char **argv, t_symtab **symtab);

#endif
