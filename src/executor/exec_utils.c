/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 16:44:08 by dsaat         #+#    #+#                 */
/*   Updated: 2022/08/23 14:00:06 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

static int	calc_num_args(t_word_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->word->flags == TOKEN_PIPE)
			break ;
		else if (list->word->flags == TOKEN_STRING)
			i++;
		else if (list->word->flags == TOKEN_GREATER
			|| list->word->flags == TOKEN_LESS
			|| list->word->flags == TOKEN_DOUBLEGREATER
			|| list->word->flags == TOKEN_DOUBLELESS)
			list = list->next;
		list = list->next;
	}
	return (i);
}

char	**create_args_array(t_word_list *list)
{
	char		**args;
	int			i;

	i = 0;
	args = malloc(sizeof(char *) * calc_num_args(list) + 1);
	while (list && list->word->flags != TOKEN_PIPE)
	{
		if (list->word->flags == TOKEN_STRING)
		{
			args[i] = list->word->word;
			i++;
		}
		if (list->word->flags == TOKEN_GREATER
			|| list->word->flags == TOKEN_LESS
			|| list->word->flags == TOKEN_DOUBLEGREATER
			|| list->word->flags == TOKEN_DOUBLELESS)
			list = list->next->next;
		else
			list = list->next;
	}
	args[i] = NULL;
	return (args);
}

// static int	check_path(char *path)
// {
// 	struct stat	sb;

// 	if (stat(path, &sb) == 0)
// 	{
// 		if (!(sb.st_mode & S_IXUSR))
// 			errno = EACCES;
// 		return (0);
// 	}
// 	return (1);
// }

static char	*get_next_path(char *path_env, char *cmd, int i, int j)
{
	char	*path;

	path = malloc(sizeof(char) * (i - j + ft_strlen(cmd) + 2));
	if (!path)
		ft_error(EXIT_FAILURE, "malloc failed");
	ft_strlcpy(path, &path_env[j], i - j + 1);
	ft_strlcpy(&path[i - j], "/", 2);
	ft_strlcpy(&path[i - j + 1], cmd, ft_strlen(cmd) + 1);
	return (path);
}

char	*search_path_var(char *cmd, t_symtab **symtab)
{
	struct stat	sb;
	char		*path_env;
	char		*path;
	int			i;
	int			j;

	i = 0;
	path_env = symtab_lookup(symtab, "PATH")->value;
	while (path_env != NULL && path_env[i])
	{
		j = i;
		while (path_env[i] && path_env[i] != ':')
			i++;
		path = get_next_path(path_env, cmd, i, j);
		if (stat(path, &sb) == 0)
			return (path);
		// if (check_path(path) == 0)
		// 	return (path);
		else
			free(path);
		if (path_env[i] == ':')
			i++;
	}
	errno = ENOENT;
	return (NULL);
}

char	*replace_dot_with_cwd(char *cmd)
{
	char	*path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	path = malloc(sizeof(char) * ft_strlen(cwd) + ft_strlen(cmd) + 1);
	if (!path)
		ft_error(EXIT_FAILURE, "malloc failed");
	ft_strlcpy(path, cwd, ft_strlen(cwd) + 1);
	ft_strlcpy(&path[ft_strlen(cwd)], cmd, ft_strlen(cmd) + 1);
	return (path);
}