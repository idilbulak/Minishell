/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/12 17:29:23 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **environ)
{
	char		*str;
	t_token		*tokens;
	t_word_list	*word_list;
	t_symtab	**symtab;

	if (argc == 1 && ft_strncmp("minishell", argv[0], 8))
	{
		symtab = malloc(sizeof(t_symtab *) * TABLE_SIZE);
		init_symtab(symtab);
		init_env_symtab(symtab, environ);
		init_signals();
		while (1)
		{
			str = readline("minishell$  ");
			if (!str)
				exit(EXIT_FAILURE);
			add_history(str);
			tokens = tokenizer(str, tokens);
			word_list = parser(tokens, symtab);
			exit_code = executor(word_list, symtab);
			free(str);
			free_tokens(tokens);
			free(word_list);
		}
	}
}
