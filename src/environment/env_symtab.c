/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_symtab.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:06:53 by dsaat         #+#    #+#                 */
/*   Updated: 2022/09/16 12:17:44 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"
#include "../../inc/parser.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <sys/stat.h>

void	ft_error(int exit_code, char *error_message)
{
	struct stat	sb;

	ft_putstr_fd("minishell: ", 2);
	if (exit_code == 127)
	{
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (exit_code == 126 && stat(error_message, &sb) == 0
		&& S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd(error_message, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else
		perror(error_message);
	if (exit_code == -1)
		g_exit_code = -1;
	else
		exit(exit_code);
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
