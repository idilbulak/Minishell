/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_helper.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:39:46 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 11:54:12 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/env.h"
#include <stdio.h>

char	*parse_quotedstring( char *str, t_token *new_token)
{
	char	*temp_str;
	int		len;

	temp_str = str;
	len = 0;
	while (*str != '"' && *str != '\'')
	{
		if (*str == '|' && *str == '>' && *str == '<')
			break ;
		len++;
		str++;
	}
	if (*str == '"')
		new_token->tokentype = TOKEN_STRING;
	else if (*str == '\'')
		new_token->tokentype = TOKEN_STRING;
	new_token->data = ft_substr(temp_str, 0, len);
	return (str);
}

char	*parse_unquotedstring(char *str, t_token *new_token)
{
	char	*temp_str;
	int		len;

	temp_str = str;
	len = 0;
	while (*str != '>' && *str != '<' && *str != '|' && *str != ' ')
	{
		len++;
		str++;
	}
	new_token->tokentype = TOKEN_STRING;
	new_token->data = ft_substr(temp_str, 0, len);
	str = ft_substr(temp_str, len - 1, ft_strlen(temp_str) - (len - 1));
	return (str);
}

char	*lessthan_helper(char *str, t_token *new_token)
{
	if (*str == '<' && *(str + 1) != '<')
	{
		new_token->tokentype = TOKEN_LESS;
		new_token->data = ft_substr(str, 0, 1);
	}
	else if (*str == '<' && *(str + 1) == '<')
	{
		new_token->tokentype = TOKEN_DOUBLELESS;
		new_token->data = ft_substr(str, 0, 2);
		str++;
	}
	return (str);
}

char	*greaterthan_helper(char *str, t_token *new_token)
{
	if (*str == '>' && *(str + 1) != '>')
	{
		new_token->tokentype = TOKEN_GREATER;
		new_token->data = ft_substr(str, 0, 1);
	}
	else if (*str == '>' && *(str + 1) == '>')
	{
		new_token->tokentype = TOKEN_DOUBLEGREATER;
		new_token->data = ft_substr(str, 0, 2);
		str++;
	}
	return (str);
}

char	*find_delimiter( char *str, t_token *new_token, t_state state)
{
	if (*str == '|')
	{
		new_token->tokentype = TOKEN_PIPE;
		new_token->data = ft_substr(str, 0, 1);
	}
	else if (*str == '<')
		str = lessthan_helper(str, new_token);
	else if (*str == '>')
	{
		str = greaterthan_helper(str, new_token);
	}
	return (str);
}
