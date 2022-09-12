/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_helper2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 21:29:45 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/12 09:40:23 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

char	*ft_helper(char *str, char *temp_str)
{
	str = temp_str;
	if (*str != '\0')
		str++;
	while (*str == ' ')
		str++;
	return (str);
}

int	check_ifexpand(t_word_list *word_list)
{
	while (word_list)
	{
		if (ft_strrchr(word_list->word->word, '$'))
			return (1);
		word_list = word_list->next;
	}
	return (0);
}

int	check_null(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->tokentype != TOKEN_null)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

t_word_list	*create_null_list(t_word_list *word_list)
{
	word_list = init_new_word(word_list);
	word_list->word->word = NULL;
	word_list->word->flags = TOKEN_null;
	return (word_list);
}

int	calculate_new_len(int len, t_symtab **symtab, char *temp)
{
	int		count;
	int		name_len;

	count = 0;
	name_len = 0;
	while (*temp)
	{
		if (*temp == '$')
		{
			temp++;
			name_len = ft_increase(temp, name_len, symtab);
			count++;
			while (expand_until(*temp))
			{
				count++;
				temp++;
			}
		}
		if (*temp != '\0' && *temp != '$')
				temp++;
	}
	len = -count + name_len;
	return (len);
}
