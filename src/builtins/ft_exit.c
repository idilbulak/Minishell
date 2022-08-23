/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:51:58 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/23 14:00:06 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	free_symtab(t_symtab **symtab)
{
	t_symtab	*tmp;
	int			i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		while (symtab[i])
		{
			tmp = symtab[i]->next;
			free(symtab[i]->name);
			free(symtab[i]->value);
			free(symtab[i]);
			symtab[i] = tmp;
		}
		i++;
	}
	free(symtab);
}

int	ft_exit(char **argv, t_symtab **symtab)
{
	int	status;

	(void)argv;
	status = 0;
	if (argv[1])
		status = ft_atoi(argv[1]);
	else
		status = g_exit_code;
	free(argv);
	free_symtab(symtab);
	printf("exit\n");
	exit(status);
}
