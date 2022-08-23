/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:51:46 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/23 14:00:06 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include <stdio.h>

int	ft_env(char **argv, t_symtab **symtab)
{
	char	**env;
	int		i;

	(void)argv;
	i = 0;
	env = create_env_array(symtab);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	delete_env_array(env);
	return (0);
}
