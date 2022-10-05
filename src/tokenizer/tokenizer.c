/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:52 by ibulak        #+#    #+#                 */
/*   Updated: 2022/10/04 15:04:55 by ibulak        ########   odam.nl         */
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
	if (check_unclosedquotes(str))
		return (error_unclosed(tokens));
	while (if_endofdata(str, state))
	{
		str = find_startofdata(str);
		str = find_startoftoken(str);
		new_token = init_token(new_token);
		str = typeoftoken(str, new_token);
		if (tokens == NULL)
			tokens = addto_emptylist(tokens, new_token);
		else if (new_token->tokentype != TOKEN_null)
			addto_end(tokens, new_token);
		else
			free (new_token);
		// str = find_startoftoken(str);
		if (*str != '\0')
			str++;
	}
	return (tokens);
}
