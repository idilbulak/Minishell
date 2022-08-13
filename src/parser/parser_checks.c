/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 13:44:20 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/13 13:44:32 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	parser_checks(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->tokentype == TOKEN_PIPE)
		{
			if (tokens->prev == NULL)
				return (-1);
			else if (tokens->next == NULL)
				return (-1);
			else if (tokens->next->tokentype == TOKEN_PIPE)
				return (-1);
		}
		else if (check_ifredirection(tokens) == 1)
		{
			if (tokens->next == NULL)
				return (-1);
			if (tokens->next->tokentype == TOKEN_PIPE)
				return (-1);
		}
		tokens = tokens->next;
	}
	return (1);
}
