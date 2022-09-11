/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 13:44:20 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/08 17:21:35 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/minishell.h"

int	parser_checks(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->tokentype == TOKEN_PIPE)
		{
			if (tokens->prev == NULL)
				return (-1);
			else if (tokens->next == NULL)
			{
				char *str = readline("> ");
				if (!str)
				{
					ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
					g_exit_code = 258;
					str = NULL;
					return (1);
				}
				t_token *new_token = NULL;
				new_token = init_token(new_token);
				new_token->tokentype = TOKEN_STRING;
				new_token->data = str;
				tokens->next = new_token;
				return (1);
			}
			else if (tokens->next->tokentype == TOKEN_PIPE)
			{
				char *str = readline("> ");
				if (!str)
				{
					ft_putstr_fd("\b minishell: syntax error: unexpected end of file\n", 2);
					g_exit_code = 258;
					str = NULL;
					return (1);
				}
				tokens = tokens->prev;
				free(tokens->next->next->data);
				free(tokens->next->next);
				free(tokens->next->data);
				free(tokens->next);
				tokens->next = NULL;
				free(str);
				// str = NULL;
				return (1);
			}
			else if (tokens->next->next->tokentype == TOKEN_PIPE)
				return (-1);
		}
		else if (check_ifredirection(tokens) == 1)
		{
			if (tokens->next == NULL)
				return (-2);
			else if (check_ifredirection(tokens->next))
				return (-3);
			else if (tokens->next->tokentype == TOKEN_PIPE
				|| check_ifredirection(tokens->next))
				return (-1);
		}
		tokens = tokens->next;
	}
	return (1);
}
