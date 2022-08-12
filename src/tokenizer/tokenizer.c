/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:52 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/12 18:12:57 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenizer.h"
#include <stdbool.h>

bool	if_endofdata(char *str, bool state)
{
	if (*str == '\0')
		state = false;
	return (state);
}

char	*find_startofdata(char *str)
{
	while (*str == '\n' || *str == '\r')
		str++;
	return (str);
}

char	*find_startoftoken(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

t_token	*tokenizer(char *str, t_token *tokens)
{
	t_token		*new_token;
	bool		state;

	state = true;
	tokens = init_tokens(tokens);
	if (!tokens)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	while (if_endofdata(str, state))
	{
		str = find_startofdata(str);
		str = find_startoftoken(str);
		new_token = init_tokens(new_token);
		str = typeoftoken(str, new_token);
		if (tokens->data == NULL)
			tokens = addto_emptylist(tokens, new_token);
		else
			addto_end(tokens, new_token);
		free(new_token);
		str++;
	}
	return (tokens);
}
