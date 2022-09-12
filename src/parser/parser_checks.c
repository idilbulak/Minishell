/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 13:44:20 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/12 12:39:17 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/minishell.h"

t_token	*pipe_without_next(t_token *tokens)
{
	char	*str;
	t_token	*new_token;

	str = readline("> ");
	if (!str)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		g_exit_code = 258;
		str = NULL;
		return (tokens);
	}
	new_token = NULL;
	new_token = init_token(new_token);
	new_token->tokentype = TOKEN_STRING;
	new_token->data = str;
	tokens->next = new_token;
	return (tokens);
}

t_token	*twopipes_without_next(t_token *tokens)
{
	char	*str;

	str = readline("> ");
	if (!str)
	{
		ft_putstr_fd("\b minishell: syntax error: unexpected end of file\n", 2);
		g_exit_code = 258;
		str = NULL;
		return (tokens);
	}
	tokens = tokens->prev;
	free(tokens->next->next->data);
	free(tokens->next->next);
	free(tokens->next->data);
	free(tokens->next);
	tokens->next = NULL;
	free(str);
	str = NULL;
	return (tokens);
}

int	parser_check_helper(t_token *t)
{
	if (t->next == NULL)
		return (-2);
	else if (check_ifredirection(t->next))
		return (-3);
	else if (t->next->tokentype == TOKEN_PIPE
		|| check_ifredirection(t->next))
		return (-1);
	return (0);
}

int	parser_checks(t_token *t)
{
	while (t)
	{
		if (t->tokentype == TOKEN_PIPE)
		{
			if (t->prev == NULL)
				return (-1);
			else if (t->next == NULL)
				t = pipe_without_next(t);
			else if (t->next->tokentype == TOKEN_PIPE && t->next->next == NULL)
				t = twopipes_without_next(t);
			else if (t->next->tokentype == TOKEN_PIPE
				&& t->next->next->tokentype == TOKEN_PIPE)
				return (-1);
		}
		else if (check_ifredirection(t) == 1)
		{
			if (parser_check_helper(t))
				return (parser_check_helper(t));
		}
		t = t->next;
	}
	return (1);
}

void	syntax_error(int e)
{
	if (e == -1)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (e == -2)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline' \
		\n", 2);
	else if (e == -3)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
}
