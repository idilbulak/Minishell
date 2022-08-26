/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:51:58 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/26 16:07:17 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_exit(char **argv, t_symtab **symtab)
{
	int	status;
	int	i;

	(void)symtab;
	status = g_exit_code;
	if (argv[1])
	{
		status = ft_atoi(argv[1]);
		i = 0;
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
			{
				// ft_putstr_fd("exit\n", 1);
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(argv[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
				// status = 255;
				// break ;
			}
			i++;
		}
	}
	if (argv[2])
	{
		
		ft_putstr_fd("this:\n", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd("\n", 2);
		// ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	// else
		// status = g_exit_code;
	// ft_putstr_fd("exit\n", 1);
	exit(status);
}



// static void	free_symtab(t_symtab **symtab)
// {
// 	t_symtab	*tmp;
// 	int			i;

// 	i = 0;
// 	while (i < TABLE_SIZE)
// 	{
// 		while (symtab[i])
// 		{
// 			tmp = symtab[i]->next;
// 			free(symtab[i]->name);
// 			free(symtab[i]->value);
// 			free(symtab[i]);
// 			symtab[i] = tmp;
// 		}
// 		i++;
// 	}
// 	free(symtab);
// }
	// free(argv);
	// free_symtab(symtab);