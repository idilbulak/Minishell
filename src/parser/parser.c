/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:24:53 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 15:01:49 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/env.h"
#include <stdio.h>

t_word_list	*parser(t_token *tokens)
{
	t_word_list	*word_list;
	t_word_list	*new_word;

	if (parser_checks(tokens) == -1)
		exit(EXIT_FAILURE);
	word_list = malloc(sizeof(t_word_list));
	if (!word_list)
		exit(EXIT_FAILURE);
	word_list = init_word_list(word_list);
	while (tokens)
	{
		new_word = NULL;
		new_word = init_new_word(new_word, tokens);
		if (word_list->word == NULL)
			addto_empty_wlist(word_list, new_word);
		else
		{
			addto_wend(word_list, new_word);
		}
		tokens = tokens->next;
	}
	return (word_list);
}