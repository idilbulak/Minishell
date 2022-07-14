/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_helper2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:38:38 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 10:53:07 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/env.h"

char	*typeoftoken(char *str, t_token *new_token, t_state state)
{
	if (*str == '|' || *str == '>' || *str == '<')
	{
		state = STATE_FindDelimiter;
		str = find_delimiter(str, new_token, state);
	}
	else
	{
		if (*str == '"' || *str == '\'')
		{
			str++;
			state = STATE_ParseQuotedString;
			str = parse_quotedstring(str, new_token);
		}
		else if (*str != '\0')
		{
			state = STATE_ParseUnquotedString;
			str = parse_unquotedstring(str, new_token);
		}
	}
	return (str);
}

t_token	*find_path(t_token *tokens)
{
	while (tokens->next != NULL)
	{
		if (tokens->tokentype == TOKEN_GREATER)
			tokens->next->tokentype = TOKEN_FILEPATH;
		if (tokens->tokentype == TOKEN_LESS)
			tokens->next->tokentype = TOKEN_FILEPATH;
		if (tokens->tokentype == TOKEN_DOUBLEGREATER)
			tokens->next->tokentype = TOKEN_FILEPATH;
		if (tokens->tokentype == TOKEN_DOUBLELESS)
			tokens->next->tokentype = TOKEN_FILEPATH;
		tokens = tokens->next;
	}
	while (tokens->prev != NULL)
		tokens = tokens->prev;
	return (tokens);
}

int	check_ifpath(t_token *tokens)
{
	while (tokens->next != NULL)
	{
		if (tokens->tokentype == 2 || tokens->tokentype == 3
			|| tokens->tokentype == 4 || tokens->tokentype == 5)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	check_ifredirection(t_token *tokens)
{
	if (tokens->tokentype == 2 || tokens->tokentype == 3
		|| tokens->tokentype == 4 || tokens->tokentype == 5)
		return (1);
	return (0);
}

int	n_token_withoutredirection(t_token *tokens)
{
	int	n;

	n = 0;
	while (tokens->next != NULL)
	{
		if (check_ifredirection(tokens) == 1)
			tokens = tokens->next;
		else
		{
			n++;
			tokens = tokens->next;
		}
	}
	return (n);
}
