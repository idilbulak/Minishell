/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/20 16:10:51 by daansaat      ########   odam.nl         */
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
#include <unistd.h>

t_env	global_env;

int	main()
{
	char		*str;
	t_token		*tokens;
	t_word_list	*word_list;

	// init_env(env);
	// init_signals();
	while (1)
	{
        str = readline("minishell$  ");
		if (!str)
			exit(EXIT_FAILURE);
		add_history(str);
		tokens = tokenizer(str, tokens);
        printf("1\n");
		// print_tokens(tokens);
		word_list = parser(tokens);
		// print_wordlist(word_list);
		executor(word_list);
		free(str);
		free(tokens);
		free(word_list);
		// str = NULL;
		printf("ïf no seg faults, say YEAYYY!\n");
	}
}

// gcc -lreadline main.c
// HISTORY_STATE *myhist = history_get_history_state ();