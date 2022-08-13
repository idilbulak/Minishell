#include "../../inc/exec.h"

void	ft_error(int exit_code, char *error_message)
{
	g_exit_code = exit_code;
	perror(error_message);
	exit(g_exit_code);
}

static int	calc_num_args(t_word_list *list)
{
	int	i;

	i = 0;	
	while (list)
	{
		if (list->word->flags == TOKEN_PIPE)
			break;
		else if (list->word->flags == TOKEN_STRING)
			i++;
		else if (list->word->flags == TOKEN_GREATER || list->word->flags == TOKEN_LESS ||
			list->word->flags == TOKEN_DOUBLEGREATER || list->word->flags == TOKEN_DOUBLELESS)
			list = list->next;
		list = list->next;
	}
	return (i);
}

char	**create_args_array(t_word_list *list)
{
	char		**args;
	int			i;

	i = 0;
	args = malloc(sizeof(char *) * calc_num_args(list) + 1);
	while (list && list->word->flags != TOKEN_PIPE)
	{
		if (list->word->flags == TOKEN_STRING)
		{
			args[i] = list->word->word;
			i++;
		}
		if (list->word->flags == TOKEN_GREATER || list->word->flags == TOKEN_LESS ||
			list->word->flags == TOKEN_DOUBLEGREATER || list->word->flags == TOKEN_DOUBLELESS)
			list = list->next->next;
		else
			list = list->next;
	}
	args[i] = NULL;
	return (args);
}
