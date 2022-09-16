/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_heredoc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 11:25:33 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/15 16:15:18 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

char	*ft_expand_heredoc(char *str, char *temp, t_symtab **symtab)
{
	char	*name;
	int		i;

	i = 0;
	while (*str != '\0')
	{
		if (check_char(str))
			temp[i++] = '$';
		else if (*str == '$')
		{
			name = find_name(str);
			if (*name == '?' || symtab_lookup(symtab, name))
				i = expand_value(name, i, temp, symtab);
			else
				str = expand_helper(str, name);
			str = fill_rest(temp, i, str, find_name(str));
		}
		else
			temp[i++] = *str;
		str++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_expander_heredoc(char *str, t_symtab **symtab)
{
	char	*temp;
	int		len;

	len = find_len(str, symtab);
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		ft_error(EXIT_FAILURE, "malloc failed");
	temp = ft_expand_heredoc(str, temp, symtab);
	free(str);
	return (temp);
}
