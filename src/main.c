/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/08 12:22:48 by ibulak        ########   odam.nl         */
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
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
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

	g_exit_code = 0;
	symtab = init_env_symtab(environ);
	register_signals();
	while (1)
	{
		str = ft_readline(original_tcattr);
		add_history(str);
		tokens = NULL;
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
