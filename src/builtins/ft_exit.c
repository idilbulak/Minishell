/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:51:58 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/14 12:23:40 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	check_valid_argument(char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
	{
		if (i == 0 && argv[1][i] == '-')
			i++;
		if (!ft_isdigit(argv[1][i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		i++;
	}
}

int	ft_exit(char **argv, t_symtab **symtab)
{
	int	status;

	status = EXIT_SUCCESS;
	if (symtab_lookup(symtab, "PIPESTATUS")->value[0] == '0')
		ft_putstr_fd("exit\n", 1);
	if (argv[1])
	{
		check_valid_argument(argv);
		status = ft_atoi(argv[1]) + 256;
		if (argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
	}
	exit(status);
}
