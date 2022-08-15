/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:24:53 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/15 19:01:56 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <stdio.h>

void	var_assignment(t_word_list *word_list, t_symtab **symtab)
{
	t_symtab	*entry;

	while (word_list)
	{
		if (word_list->word->flags == TOKEN_ENV)
		{
			ft_split_quotes(word_list);
			entry = new_entry(word_list->word->word);
			if (symtab_lookup(symtab, entry->name))
				symtab_delete(symtab, entry->name);
			symtab_insert(symtab, entry);
		}
		word_list = word_list->next;
	}
}
// 25 lines
int	parse_string_helper(char *str, int len)
{
	while (*str != ' ' && *str != '\0')
	{
		if (*str == '"')
		{
			str = str + 1;
			len++;
			while (*str != '"')
			{
				len++;
				str++;
			}
		}
		if (*str == '\'')
		{
			str = str + 1;
			len++;
			while (*str != '\'')
			{
				len++;
				str++;
			}
		}
		len++;
		str++;
	}
	return (len);
}
// 25 lines
t_word_list	*parse_string(char *str, t_word_list *word_list)
{
	char		*temp_str;
	t_word_list	*new_word;
	int			len;

	while (*str != '\0')
	{
		while (*str == ' ')
			str++;
		len = 0;
		temp_str = str;
		new_word = NULL;
		new_word = init_new_word(new_word);
		len = parse_string_helper(str, len);
		new_word->word->flags = TOKEN_STRING;
		new_word->word->word = ft_substr(temp_str, 0, len);
		if (word_list == NULL)
			word_list = addto_empty_wlist(word_list, new_word);
		else
			word_list = addto_wend(word_list, new_word);
		while (len-- > 0)
			temp_str++;
		str = temp_str;
		if (*str != '\0')
			str++;
	}
	return (word_list);
}

t_word_list	*create_word_list(t_token *tokens, t_word_list *word_list)
{
	t_word_list	*new_word;

	while (tokens)
	{
		if (tokens->tokentype == TOKEN_STRING)
			word_list = parse_string(tokens->data, word_list);
		else
		{
			new_word = NULL;
			new_word = init_new_word(new_word);
			new_word->word->word = tokens->data;
			new_word->word->flags = tokens->tokentype;
			if (word_list == NULL)
				word_list = addto_empty_wlist(word_list, new_word);
			else
				word_list = addto_wend(word_list, new_word);
		}
		tokens = tokens->next;
	}
	return (word_list);
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
// extra funtions move them to another file
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

t_word_list	*parser(t_token *tokens, t_symtab **symtab)
{
	t_word_list	*word_list;

	word_list = NULL;
	if (parser_checks(tokens) == -1)
	{
		perror("syntax");
		return (NULL);
	}
	if (check_null(tokens))
		create_null_list(word_list);
	else
	{
		word_list = create_word_list(tokens, word_list);
		check_env(word_list);
		adjust_wordlist(word_list);
		if (check_ifexpand(word_list) == 1)
			ft_expander(word_list, symtab);
		ft_split_quotes(word_list);
		var_assignment(word_list, symtab);
	}
	return (word_list);
}
