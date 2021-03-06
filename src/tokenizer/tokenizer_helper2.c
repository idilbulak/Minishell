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

char	*typeoftoken(char *str, t_token *new_token)
{
	if (*str == '|' || *str == '>' || *str == '<')
		str = find_delimiter(str, new_token);
	else
	{
		if (*str == '"' || *str == '\'')
			str = parse_quotedstring(str, new_token);
		else if (*str != '\0')
			str = parse_unquotedstring(str, new_token);
	}
	return (str);
}

t_token	*find_path(t_token *tokens)
{
	// while(tokens->next)
	// {
	// 	if (check_ifredirection(tokens) == 1)
	// 	{
	// 	printf("err\n");
	// 		while(check_ifredirection(tokens) == 1)
	// 			tokens = tokens->next;
	// 		tokens->tokentype = TOKEN_FILEPATH;
	// 	}
	// 	// tokens = tokens->next;
		
	// }
	// while (tokens->prev)
	// 	tokens = tokens->prev;
	return (tokens);
}

int	check_ifpath(t_token *tokens)
{
	while(tokens->next)
	{
		if (check_ifredirection(tokens) == 1)
		{
			while(check_ifredirection(tokens) == 1)
				tokens = tokens->next;
			return (1);
		}
		tokens = tokens->next;
	}
	while (tokens->prev)
		tokens = tokens->prev;
	return (0);
}

int	check_ifredirection(t_token *tokens)
{
	if (tokens->tokentype == 2 || tokens->tokentype == 3
		|| tokens->tokentype == 4 || tokens->tokentype == 5)
		return (1);
	return (0);
}
