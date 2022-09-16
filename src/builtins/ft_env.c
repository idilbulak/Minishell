/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 14:51:46 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/16 13:16:28 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../libft/libft.h"
#include <stdio.h>

int	ft_env(char **argv, t_symtab **symtab)
{
	char	**env;
	int		i;

	(void)argv;
	i = 0;
	if (argv[1])
	{
		ft_putstr_fd("minishell: env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return (2);
	}
	env = create_env_array(symtab);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	delete_env_array(env);
	return (0);
}
