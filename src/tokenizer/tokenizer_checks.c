/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_checks.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:38:38 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/12 17:33:43 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenizer.h"

int	check_ifpath(t_token *tokens)
{
	while (tokens)
	{
		if (check_ifredirection(tokens) == 1)
		{
			while (check_ifredirection(tokens) == 1)
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
