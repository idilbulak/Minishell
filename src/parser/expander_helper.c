/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_helper.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 21:14:59 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/31 10:56:27 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	name_len(char *str)
{
	int	count;

	count = 0;
	while (*str != '$' && *str != '\0' && *str != '"'
		&& *str != '\'' && *str != ' ')
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

int	find_name_len(int name_len, t_symtab **symtab, char *name)
{
	char	*value;

	value = NULL;
	if (symtab_lookup(symtab, name))
	{
		value = symtab_lookup(symtab, name)->value;
		name_len += ft_strlen(value);
	}
	if (!symtab_lookup(symtab, name))
		name_len += 1;
	else if (ft_strcmp(name, "?"))
		name_len += 3;
	return (name_len);
}

int	ft_increase(char *str, int name_len, t_symtab **symtab )
{
	int		len;
	char	*temp;
	char	*name;

	len = 0;
	temp = str;
	while (*temp != '$' && *temp != ' ' && *temp != '\''
		&& *temp != '"' && *temp != '\0')
	{
		len++;
		temp++;
	}
	name = ft_substr(str, 0, len);
	name_len = find_name_len(name_len, symtab, name);
	free(name);
	return (name_len);
}
