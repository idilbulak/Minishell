/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/08 16:43:43 by dsaat         ########   odam.nl         */
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
#include "../inc/environment.h"
#include <unistd.h>

int	main()
{
	int         exit_code;
    char		*str;
	t_token		*tokens;
	t_word_list	*word_list;
	t_symtab	**symtab;

	symtab = malloc(sizeof(t_symtab *) * TABLE_SIZE);
	init_symtab(symtab);
	init_env_symtab(symtab);
	init_signals();
	while (1)
	{
        str = readline("minishell$  ");
		if (!str)
			exit(EXIT_FAILURE);
		add_history(str);
		tokens = tokenizer(str, tokens);
		// print_tokens(tokens);
		word_list = parser(tokens);
		// print_wordlist(word_list);
		exit_code = executor(word_list, symtab);
        // printf("exit_code = %d\n", exit_code);
		free(str);
		free(tokens);
		free(word_list);
		// str = NULL;
		// printf("ïf no seg faults, say YEAYYY!\n");
	}
}

// gcc -lreadline main.c
// HISTORY_STATE *myhist = history_get_history_state ();