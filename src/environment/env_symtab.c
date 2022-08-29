/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_symtab.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:06:53 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/29 16:11:26 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <stdio.h>

void	ft_error(int exit_code, char *error_message)
{
	g_exit_code = exit_code;
	if (exit_code == 127)
	{
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
		perror(error_message);
	exit(g_exit_code);
}

t_symtab	**init_env_symtab(char **environ)
{
	t_symtab	**symtab;
	t_symtab	*entry;
	int			i;

	symtab = malloc(sizeof(t_symtab *) * TABLE_SIZE);
	if (!symtab)
		perror("malloc failed");
	i = 0;
	while (i < TABLE_SIZE)
	{
		symtab[i] = NULL;
		i++;
	}
	i = 0;
	while (environ[i])
	{
		entry = new_entry(environ[i]);
		entry->flag = FLAG_EXPORT;
		symtab_insert(symtab, entry);
		i++;
	}
	return (symtab);
}
