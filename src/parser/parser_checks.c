#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/env.h"
#include <stdio.h>

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