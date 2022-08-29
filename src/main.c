/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/29 16:33:24 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_minishell(char **environ)
{
	char		*str;
	t_token		*tokens;
	t_word_list	*word_list;
	t_symtab	**symtab;

	symtab = init_env_symtab(environ);
	init_signals();
	while (1)
	{
		str = readline("minishell$  ");
		if (!str)
			exit(EXIT_FAILURE);
		add_history(str);
		tokens = tokenizer(str, tokens);
		word_list = parser(tokens, symtab);
		executor(word_list, symtab);
		free(str);
		free_tokens(tokens);
		free_word_list(word_list);
		str = NULL;
	}
}

int	main(int argc, char **argv, char **environ)
{
	(void)argv;
	if (argc == 1)
		init_minishell(environ);
	return (0);
}
