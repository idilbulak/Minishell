/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenlist_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:51:34 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/13 16:24:20 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenizer.h"
#include <stdio.h>

#define GREEN "\033[38;5;2m"
#define RESET "\033[38;5;255m"
#define RED "\033[38;5;1m"
#define BLUE "\033[38;5;4m"
#define PURPLE "\033[0;35m"
#define YELLOW "\033[0;33m"

t_token	*init_token(t_token *token)
{
	token = malloc(sizeof(t_token));
	if (!token)
		ft_error(EXIT_FAILURE, "malloc failed");
	token->next = NULL;
	token->data = NULL;
	token->prev = NULL;
	token->tokentype = TOKEN_null;
	return (token);
}

t_token	*addto_emptylist(t_token *tokens, t_token *new)
{
	tokens = new;
	return (tokens);
}

t_token	*addto_end(t_token *tokens, t_token *new)
{
	t_token	*prev;

	prev = tokens;
	while (prev->next != NULL)
		prev = prev->next;
	prev->next = new;
	new->prev = prev;
	return (tokens);
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->data);
		free(tokens);
		tokens = temp;
	}
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
		printf("%s\n", current -> data);
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
