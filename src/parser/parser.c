/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:24:53 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/12 18:48:04 by ibulak        ########   odam.nl         */
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
			entry = new_entry(word_list->word->word);
			if (symtab_lookup(symtab, entry->name))
				symtab_delete(symtab, entry->name);
			symtab_insert(symtab, entry);
		}
		word_list = word_list->next;
	}
}

char	*parse_string_helper(char *str, t_word_list *word_list)
{
	char		*temp_str;
	char		*new_str;
	t_word_list	*new_word;
	int			len;

	temp_str = str;
	len = 0;
	new_word = NULL;
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
	new_str = ft_substr(temp_str, 0, len);
	new_word = init_new_str(new_word, new_str);
	if (word_list->word == NULL)
		addto_empty_wlist(word_list, new_word);
	else
		addto_wend(word_list, new_word);
	str = ft_substr(temp_str, len - 1, ft_strlen(temp_str) - (len - 1));
	return (str);
}

t_word_list	*parse_string(t_token *tokens, t_word_list *word_list)
{
	char	*str;

	str = tokens->data;
	while (*str != '\0')
	{
		while (*str == ' ')
			str++;
		str = parse_string_helper(str, word_list);
		str++;
	}
	return (word_list);
}

t_word_list	*parser(t_token *tokens, t_symtab **symtab)
{
	t_word_list	*word_list;
	t_word_list	*new_word;

	if (parser_checks(tokens) == -1)
	{
		perror("syntax");
		// sig_handler(SIGINT);
		return (NULL);
	}
	word_list = NULL;
	word_list = init_word_list(word_list);
	if (!word_list)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	while (tokens)
	{
		if (tokens->tokentype == TOKEN_STRING)
			word_list = parse_string(tokens, word_list);
		else
		{
			new_word = NULL;
			new_word = init_new_word(new_word, tokens);
			if (word_list->word == NULL)
				addto_empty_wlist(word_list, new_word);
			else
			{
				addto_wend(word_list, new_word);
			}
		}
		tokens = tokens->next;
	}
	check_env(word_list);
	adjust_wordlist(word_list);
	ft_expander(word_list, symtab);
	ft_split_quotes(word_list);
	var_assignment(word_list, symtab);
	return (word_list);
}
