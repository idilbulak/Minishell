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

int	calculate_n_args(t_token *tokens)
{
	int	n;

	n = 0;
	while(tokens->prev != NULL)
		tokens = tokens->prev;
	while (tokens->data != NULL)
	{
		if (tokens->tokentype == TOKEN_PIPE)
			tokens = tokens->next;
		n++;
		tokens = tokens->next;
	}
	return (n);
}

int	calculate_n_cmd(t_token *tokens)
{
	int	n;

	n = 0;
	while(tokens->prev != NULL)
		tokens = tokens->prev;
	while (tokens->data != NULL)
	{
		if (tokens->tokentype == TOKEN_PIPE)
			tokens = tokens->next;
		if (tokens->tokentype == TOKEN_FILEPATH)
			tokens = tokens->next;
		if (check_ifredirection(tokens) == 1)
			tokens = tokens->next;
		else
			n++;
		tokens = tokens->next;
	}
	return (n);
}

int	calculate_n_str(t_token *tokens)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = 1;
	str = tokens->data;
	while (str[i] != '\0')
	{
		if(str[i] == ' ')
			n++;
		i++;
	}
	return (n);
}

char	**split_token(t_token *tokens)
{
	char	**data;

	if (tokens->tokentype == TOKEN_FILEPATH)
	{
		data = malloc(sizeof(char *) * 2);
		data[0] = tokens->data;
		data[1] = NULL;
	}
	else
		data = ft_split(tokens->data, ' ');
	return (data);
}

t_word_list	*parser(t_token *tokens)
{
	t_word_list	*word_list;
	t_word_list	*new_word;

	if (parser_checks(tokens) == -1)
		exit(EXIT_FAILURE);
	word_list = init_word_list(word_list);
	while (tokens->data != NULL)
	{
		new_word = init_new_word(new_word, tokens);
		if (word_list->word == NULL)
			word_list = addto_empty_wlist(word_list, new_word);
		else
			addto_wend(word_list, new_word);
		tokens = tokens->next;
	}
	// i = 0;
	// n = calculate_n_args(tokens);
	// while (i < n)
	// {
	// 	if (tokens->tokentype == TOKEN_PIPE)
	// 		tokens = tokens->next;
	// 	if (tokens->tokentype == TOKEN_STRING)
	// 	{
	// 		tree->args[i]->type = TOKEN_STRING;
	// 		tree->args[i]->data = split_token(tokens);
	// 	}
	// 	if (check_ifredirection(tokens) == 1)
	// 	{
	// 		tree->args[i]->type = tokens->tokentype;
	// 			tokens = tokens->next;
			
	// 		tree->args[i]->data = split_token(tokens);
	// 	}
	// 	if(tokens->data != NULL)
	// 		tokens = tokens->next;
	// 	i++;
	// }
	// tree->args[n] = malloc(sizeof(t_args));
	// tree->args[n] = NULL;
	
	return (word_list);
}