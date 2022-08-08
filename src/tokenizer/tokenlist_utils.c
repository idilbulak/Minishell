/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenlist_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:51:34 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 10:58:06 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/env.h"
#include <stdio.h>

#define GREEN "\033[38;5;2m"
#define RESET "\033[38;5;255m"
#define RED "\033[38;5;1m"
#define BLUE "\033[38;5;4m"
#define PURPLE "\033[0;35m"
#define YELLOW "\033[0;33m"

t_token	*init_tokens(t_token *tokens)
{
	tokens = malloc(sizeof(t_token));
	if (!tokens)
	{	
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	tokens->next = NULL;
	tokens->data = NULL;
	tokens->prev = NULL;
	tokens->tokentype = TOKEN_null;
	return (tokens);
}

t_token	*addto_emptylist(t_token *head, t_token *new)
{
	head->data = new->data;
	head->tokentype = new->tokentype;
	return (head);
}

t_token	*addto_end(t_token *head, t_token *new)
{
	t_token	*temp_prev;
	t_token	*temp_next;

	temp_next = malloc(sizeof(t_token));
	if (!temp_next)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	temp_next->prev = NULL;
	temp_next->data = new->data;
	temp_next->tokentype = new->tokentype;
	temp_next->next = NULL;
	temp_prev = head;
	while (temp_prev->next != NULL)
		temp_prev = temp_prev->next;
	temp_prev->next = temp_next;
	temp_next->prev = temp_prev;
	return (head);
}

void	print_tokens(t_token *head)
{
	t_token	*current;
	int		i;

	current = head;
	i = 0;
	if (!head)
		return ;
	printf("\n");
	printf("%s------------------- TOKENS -------------------%s\n\n", BLUE, RESET);
	while (current != NULL )
	{
		printf(YELLOW);
		printf("token [%d]:  ", i);
		printf("%s\n",  current -> data);
		printf(GREEN);
		printf("type: %u", current->tokentype);
		printf("\n");
		printf(RESET);
		i++;
		current = current->next;
	}
	printf("\n");
	free(current);
}

