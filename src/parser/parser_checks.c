#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/env.h"
#include <stdio.h>

int	if_pipe(t_token *tokens)
{
	while (tokens->next != NULL)
	{
		if (tokens->tokentype == 1)
			return(42);
		tokens = tokens->next;
	}
	return (-1);
}

int	check_pipe(t_token *tokens)
{
	if (tokens->tokentype == TOKEN_PIPE)
		return (-1);
	while (tokens->data != NULL)
	{
		if (tokens->tokentype == TOKEN_PIPE)
		{
			if (tokens->next->data == NULL)
				return (-1);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	check_redirection(t_token *tokens)
{
	while (tokens->data != NULL)
	{
		if (check_ifredirection(tokens) == 1)
		{
			if (tokens->next->data == NULL)
				return (-1);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	parser_checks(t_token *tokens)
{
	int	n;

	n = 0;
	if (if_pipe(tokens) == 42)
		n = check_pipe(tokens);
	if (check_ifpath(tokens) == 1)
		n = check_redirection(tokens);
	return (n);
}