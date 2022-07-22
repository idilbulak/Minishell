/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 12:29:45 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 12:32:52 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/env.h"
#include <stdio.h>

t_word_list	*init_word_list(t_word_list *word_list)
{
	word_list = malloc(sizeof(t_word_list));
	if (!word_list)
		exit(EXIT_FAILURE);
	word_list->next = NULL;
	word_list->word = NULL;
	return (word_list);
}

t_word_list	*init_new_word(t_word_list *new_word, t_token *tokens)
{
	new_word = malloc(sizeof(t_word_list));
	if (!new_word)
		exit(EXIT_FAILURE);
	new_word->next = NULL;
	new_word->word = malloc(sizeof(t_word_desc));
	if (!new_word->word)
		exit(EXIT_FAILURE);
	new_word->word->flags = tokens->tokentype;
	new_word->word->word = tokens->data;
	return (new_word);
}

t_word_list	*addto_wend(t_word_list *head, t_word_list *new)
{
	t_word_list	*temp_next;

	temp_next = malloc(sizeof(t_word_list));
	temp_next->word = new->word;
	temp_next->next = NULL;
	while (head->next != NULL)
		head = head->next;
	head->next = temp_next;
	return (head);
}

t_word_list	*addto_empty_wlist(t_word_list *head, t_word_list *new)
{
	head->word = new->word;
	head->next = NULL;
	return (head);
}

void	print_wordlist(t_word_list *word_list)
{
	int	i;
	i = 0;
	while(word_list != NULL)
	{
		printf("word_list[%d]: \n", i);
		printf("\t word: %s\n", word_list->word->word);
		printf("\t flag: %d\n", word_list->word->flags);
		i++;
		word_list = word_list->next;
	}
}