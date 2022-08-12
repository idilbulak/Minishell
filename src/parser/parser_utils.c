/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 12:29:45 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/12 16:27:07 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <stdio.h>

#define GREEN "\033[38;5;2m"
#define RESET "\033[38;5;255m"
#define RED "\033[38;5;1m"
#define BLUE "\033[38;5;4m"
#define PURPLE "\033[0;35m"
#define YELLOW "\033[0;33m"

t_word_list	*init_word_list(t_word_list *word_list)
{
	word_list = malloc(sizeof(t_word_list));
	if (!word_list)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	word_list->next = NULL;
	word_list->word = NULL;
	return (word_list);
}

t_word_list	*init_new_word(t_word_list *new_word, t_token *tokens)
{
	new_word = malloc(sizeof(t_word_list));
	if (!new_word)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	new_word->next = NULL;
	new_word->word = malloc(sizeof(t_word_desc));
	if (!new_word->word)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	new_word->word->flags = tokens->tokentype;
	new_word->word->word = tokens->data;
	return (new_word);
}

t_word_list	*addto_wend(t_word_list *head, t_word_list *new)
{
	t_word_list	*temp_next;

	temp_next = malloc(sizeof(t_word_list));
	if (!temp_next)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
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

t_word_list	*init_new_str(t_word_list *new_word, char *new_str)
{
	new_word = malloc(sizeof(t_word_list));
	if (!new_word)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	new_word->next = NULL;
	new_word->word = malloc(sizeof(t_word_desc));
	if (!new_word->word)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	new_word->word->flags = TOKEN_STRING;
	new_word->word->word = new_str;
	return (new_word);
}

void	print_wordlist(t_word_list *word_list)
{
	int	i;
	i = 0;
	printf("%s------------------ WORD_LIST -----------------%s\n\n", BLUE, RESET);
	while(word_list != NULL)
	{
		printf(YELLOW);
		printf("word_list [%d]: \n", i);
		printf(PURPLE);
		printf("\t word: %s\n", word_list->word->word);
		printf(GREEN);
		printf("\t flag: %d\n\n", word_list->word->flags);
		printf(RESET);
		i++;
		word_list = word_list->next;
	}
	printf("%s----------------------------------------------%s\n\n", BLUE, RESET);
}