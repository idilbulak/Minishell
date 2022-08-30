/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/30 13:25:23 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <termios.h>

char	*ft_readline(struct termios original_tcattr)
{
	char			*str;
	struct termios	new_tcattr;

	tcgetattr(STDIN_FILENO, &original_tcattr);
	tcgetattr(STDIN_FILENO, &new_tcattr);
	new_tcattr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tcattr);
	register_signals();
	str = readline("minishell$ ");
	if (!str)
		exit(EXIT_FAILURE);
	tcsetattr(STDIN_FILENO, TCSANOW, &original_tcattr);
	unregister_signals();
	return (str);
}

static void	init_minishell(char **environ, struct termios original_tcattr)
{
	char		*str;
	t_token		*tokens;
	t_word_list	*word_list;
	t_symtab	**symtab;

	symtab = init_env_symtab(environ);
	register_signals();
	while (1)
	{
		str = ft_readline(original_tcattr);
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
	struct termios	original_tcattr;

	(void)argv;
	tcgetattr(STDIN_FILENO, &original_tcattr);
	if (argc == 1)
		init_minishell(environ, original_tcattr);
	return (0);
}
