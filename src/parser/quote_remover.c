/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_remover.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 13:48:07 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/13 14:03:08 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <stdio.h>

int	check_qmode(char str, int mode)
{
	if (str == '\'' && mode == 0)
		mode = 1;
	else if (str == '"' && mode == 0)
		mode = 2;
	else if (str == '\'' && mode == 1)
		mode = 0;
	else if (str == '"' && mode == 2)
		mode = 0;
	return (mode);
}

void	ft_split_quotes(t_word_list *word_list)
{
	char	*str;
	char	*temp;
	int		mode;
	int		i;

	while (word_list)
	{
		mode = 0;
		temp = malloc(sizeof(char ));
		if (!temp)
		{
			perror ("malloc()");
			exit (EXIT_FAILURE);
		}
		if (word_list->word->flags == TOKEN_STRING)
		{
			str = word_list->word->word;
			i = 0;
			while (*str != '\0')
			{
				mode = check_qmode(*str, mode);
				if ((*str != '\'' || mode != 1) && (*str != '\'' || mode != 0)
					&& (*str != '"' || mode != 2) && (*str != '"' || mode != 0))
				{
					temp[i] = *str;
					i++;
				}
				str++;
			}
			free (word_list->word->word);
			word_list->word->word = temp;
		}
		word_list = word_list->next;
	}
}
