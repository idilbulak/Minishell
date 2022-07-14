/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 15:01:29 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../inc/tokenizer.h"
#include "../inc/parser.h"
#include "../inc/exec.h"
#include "../inc/env.h"
#include "../inc/signals.h"
#include <stdio.h>

t_env	global_env;

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_token	*tokens;
	t_ast	*tree;

	// init_env(env);
	init_signals();
	while (1)
	{
		str = readline("MINIHELL> ");
		if (!str)
			exit(EXIT_FAILURE);
		add_history(str);
		tokens = tokenizer(str, tokens);
		// // print_tokens(tokens);
		tree = parser(tokens);
		// // print_tree(tree, tokens);
		executor(tree);
		free(str);
		free(tokens);
		free(tree);
		// str = NULL;
	}
}

// gcc -lreadline main.c
// HISTORY_STATE *myhist = history_get_history_state ();