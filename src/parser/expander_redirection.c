/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_redirection.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 11:25:33 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/05 11:36:39 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// if (check_ifexpand(str) == 1)
// 			ft_expander(str, symtab);

int	check_ifexpand_redirection(char *str)
{
	if (ft_strrchr(word_list->word->word, '$'))
		return (1);
	return (0);
}

char	*ft_expand_redirection(char *str, char *temp, t_symtab **symtab)
{
	char	*name;
	int		i;

	i = 0;
	while (*str != '\0')
	{
		if (*str == '$')
		{
			name = find_name(str);
			if (*name == '?' || symtab_lookup(symtab, name))
				i = expand_value(name, i, temp, symtab);
			else
				str = expand_helper(str, name);
			str = fill_rest(temp, i, str, name);
		}
		else
		{
			temp[i] = *str;
			i++;
		}
		str++;
	}
	temp[i] = '\0';
	return (temp);
}

void	ft_expander_redirection(char *str, t_symtab **symtab)
{
	char	*temp;
	int		len;

	len = find_len(str, symtab);
	temp = malloc(sizeof(char) * len);
	if (!temp)
		ft_error(EXIT_FAILURE, "malloc failed");
	temp = ft_expand_redirection(str, temp, symtab);
	free(str);
	str = temp;
}
