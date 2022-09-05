/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_heredoc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 11:25:33 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/05 11:49:23 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// if (check_ifexpand_heredoc(str) == 1)
// 			ft_expander_heredoc(str, symtab);

// int	check_ifexpand_heredoc(char *str)
// {
// 	if (ft_strrchr(word_list->word->word, '$'))
// 		return (1);
// 	return (0);
// }

char	*ft_expand_heredoc(char *str, char *temp, t_symtab **symtab)
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

char	*ft_expander_heredoc(char *str, t_symtab **symtab)
{
	char	*temp;
	int		len;

	len = find_len(str, symtab);
	temp = malloc(sizeof(char) * len);
	if (!temp)
		ft_error(EXIT_FAILURE, "malloc failed");
	temp = ft_expand_heredoc(str, temp, symtab);
	free(str);
	return (temp);
}
