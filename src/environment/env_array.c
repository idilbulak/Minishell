/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_array.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:27:18 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/12 15:27:43 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/environment.h"

int	total_export_entries(t_symtab **symtab)
{
	t_symtab	*tmp;
	int			i;
	int			num;

	i = 0;
	num = 0;
	while (i < TABLE_SIZE)
	{
		tmp = symtab[i];
		while (tmp)
		{
			if (tmp->flag == FLAG_EXPORT)
				num++;
			tmp = tmp->next;
		}
		i++;
	}
	return (num);
}

static char	*make_str_from_struct(t_symtab *tmp)
{
	char	*str;
	int		name;
	int		value;

	name = ft_strlen(tmp->name);
	value = ft_strlen(tmp->value);
	str = malloc(sizeof(char) * (name + value + 2));
	ft_strlcpy(str, tmp->name, name + 1);
	ft_strlcpy(&str[name], "=", 2);
	ft_strlcpy(&str[name + 1], tmp->value, value + 1);
	return (str);
}

char	**create_env_array(t_symtab **symtab)
{
	char		**env;
	t_symtab	*tmp;
	int			i;
	int			j;

	env = malloc(sizeof(char *) * total_export_entries(symtab) + 1);
	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		tmp = symtab[i];
		while (tmp)
		{
			if (tmp->flag == FLAG_EXPORT)
			{
				env[j] = make_str_from_struct(tmp);
				j++;
			}
			tmp = tmp->next;
		}
		i++;
	}
	env[j] = NULL;
	return (env);
}

void	delete_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
