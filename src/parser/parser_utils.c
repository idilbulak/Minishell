/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 12:29:45 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/12 18:48:22 by ibulak        ########   odam.nl         */
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

t_word_list	*init_new_word(t_word_list *new_word)
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
	new_word->word->flags = 0;
	new_word->word->word = NULL;
	return (new_word);
}

t_word_list	*addto_wend(t_word_list *word_list, t_word_list *new)
{
	t_word_list	*temp;

	temp = word_list;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (word_list);
}

t_word_list	*addto_empty_wlist(t_word_list *word_list, t_word_list *new)
{
	word_list = new;
	return (word_list);
}

void	free_word_list(t_word_list *word_list)
{
	t_word_list	*temp;

	while (word_list)
	{
		temp = word_list->next;
		if (word_list->word->flags == TOKEN_STRING)
			free(word_list->word->word);
		free(word_list->word);
		free(word_list);
		word_list= temp;
	}
}

void	print_wordlist(t_word_list *word_list)
{
	int	i;

	i = 0;
	printf("%s------------------ WORD_LIST -----------------%s\n\n", BLUE, RESET);
	while (word_list != NULL)
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
