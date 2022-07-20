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

t_token	*init_tokens(t_token *tokens)
{
	tokens = malloc(sizeof(t_token));
	if (!tokens)
		exit(EXIT_FAILURE);
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
	while (current != NULL )
	{
		printf("token[%d]:%s type:%u", i, current -> data, current->tokentype);
		printf("\n");
		i++;
		current = current->next;
	}
	printf("\n");
	free(current);
}

