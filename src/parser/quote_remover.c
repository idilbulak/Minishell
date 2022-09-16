/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_remover.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 13:48:07 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/16 12:11:14 by ibulak        ########   odam.nl         */
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

char	*qremover(char *str, int mode, char *temp)
{
	int	i;

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
	if (temp[i] != '\0')
		temp[i] = '\0';
	return (temp);
}

void	ft_split_quotes(t_word_list *word_list)
{
	char	*temp;
	int		mode;

	while (word_list)
	{
		mode = 0;
		temp = word_list->word->word;
		if (!temp)
			ft_error(EXIT_FAILURE, "malloc failure");
		if (word_list->word->flags == TOKEN_STRING
			|| word_list->word->flags == TOKEN_ENV)
		{
			temp = qremover(word_list->word->word, mode, temp);
			word_list->word->word = temp;
		}
		word_list = word_list->next;
	}
}

int	expand_until(char temp)
{
	if (temp != '$' && temp != '\0' && temp != '"'
		&& temp != '\'' && temp != ' ' && temp != '?'
		&& temp != '/' && temp != '#' && temp != '%'
		&& temp != '*' && temp != '+' && temp != ','
		&& temp != '=' && temp != '-' && temp != ':'
		&& temp != '.')
		return (1);
	else
		return (0);
}

int	check_char(char *str)
{
	if (*str == '$' && (*(str + 1) == ' ' || *(str + 1) == '\0'
			|| *(str + 1) == '/' || *(str + 1) == '%' || *(str + 1) == '+'
			|| *(str + 1) == ',' || *(str + 1) == '='
			|| *(str + 1) == ':' || *(str + 1) == '.'))
		return (1);
	else
		return (0);
}
