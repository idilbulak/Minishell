/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_helper.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 21:14:59 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/25 21:16:29 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	name_len(char *str)
{
	int	count;

	count = 0;
	while (*str != '$' && *str != '\0' && *str != '"')
	{
		if (*str == '?')
			return (1);
		count++;
		str++;
	}
	return (count);
}

char	*find_name(char *str)
{
	int		len;
	int		i;
	char	*name;

	str++;
	i = 0;
	len = name_len(str);
	name = malloc(sizeof(char *) * len);
	while (len > 0)
	{
		name[i] = *str;
		i++;
		str++;
		len--;
	}
	return (name);
}

char	*expand_helper(char *str, char *name)
{
	while (*str != '$')
		str++;
	free(name);
	return (str);
}
