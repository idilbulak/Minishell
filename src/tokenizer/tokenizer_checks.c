/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_checks.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:38:38 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/16 10:13:33 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"

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

int	check_unclosedquotes(char *str)
{
	int	mode;
	int	count_1;
	int	count_2;

	mode = 0;
	count_1 = 0;
	count_2 = 0;
	while (*str)
	{
		mode = check_qmode(*str, mode);
		if ((mode == 1 && *str == '\'') || (mode == 0 && *str == '\''))
			count_1++;
		if ((mode == 2 && *str == '"') || (mode == 0 && *str == '"'))
			count_2++;
		str++;
	}
	if (count_1 % 2 || count_2 % 2)
		return (1);
	return (0);
}
