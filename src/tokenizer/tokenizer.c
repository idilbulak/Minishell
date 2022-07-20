/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:52 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 11:55:22 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenizer.h"

t_state	if_endofdata(char *str, t_state state)
{
	if (*str == '\0')
		state = STATE_EndOfData;
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
	t_state		state;

	state = STATE_FindStartOfData;
	tokens = init_tokens(tokens);
	while (state != STATE_ParseError && state != STATE_EndOfData)
	{
		state = if_endofdata(str, state);
		str = find_startofdata(str);
		str = find_startoftoken(str);
		new_token = init_tokens(new_token);
		str = typeoftoken(str, new_token);
		if (tokens->data == NULL)
			tokens = addto_emptylist(tokens, new_token);
		else
			addto_end(tokens, new_token);
		str++;
	}
	if (check_ifpath(tokens) == 1)
		tokens = find_path(tokens);
	return (tokens);
}
