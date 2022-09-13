/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_helper.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 13:44:15 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/13 11:56:32 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <stdio.h>

void	check_env(t_word_list *word_list)
{
	char	*str;
	int		var;

	while (word_list)
	{
		if (word_list->word->flags == TOKEN_STRING)
		{
			str = word_list->word->word;
			var = 0;
			str++;
			while (*str != '\0')
			{
				if (*str == '=')
				{
					var = 1;
					break ;
				}
				str++;
			}
			if (var == 1)
				word_list->word->flags = TOKEN_ENV;
		}
		word_list = word_list->next;
	}
}

void	check_envorder(t_word_list *word_list)
{
	while (word_list->next)
	{
		if (word_list->word->flags == TOKEN_STRING)
		{
			if (word_list->next->word->flags == TOKEN_ENV)
				word_list->next->word->flags = TOKEN_STRING;
		}
		if (word_list->word->flags == TOKEN_ENV)
		{
			if (word_list->next->word->flags != TOKEN_ENV
				&& word_list->next->word->flags != TOKEN_null)
				word_list->word->flags = TOKEN_CENV;
		}
		word_list = word_list->next;
	}
}

void	check_validenv(t_word_list *word_list)
{
	char	*str;

	str = NULL;
	while (word_list)
	{
		if (word_list->word->flags == TOKEN_ENV)
		{
			str = word_list->word->word;
			if (ft_isdigit(*str))
				word_list->word->flags = TOKEN_STRING;
			else
			{
				while (*str != '=')
				{
					if (!ft_isalpha(*str) && !ft_isdigit(*str) && *str != '-')
						word_list->word->flags = TOKEN_STRING;
					str++;
				}
			}
		}
		word_list = word_list->next;
	}
}

void	adjust_wordlist(t_word_list *word_list)
{
	int	end;

	end = 0;
	check_envorder(word_list);
	check_validenv(word_list);
	while (word_list->next)
	{
		if (word_list->word->flags == TOKEN_STRING)
		{
			end = ft_strlen(word_list->word->word);
			word_list->word->word[end] = '\0';
		}
		if (word_list->word->flags == TOKEN_ENV)
		{
			if (word_list->next->word->flags == TOKEN_CENV)
				word_list->word->flags = TOKEN_CENV;
		}
		word_list = word_list->next;
	}
}

char	*fill_rest(char *temp, int i, char *str, char *name)
{
	int	len;

	len = ft_strlen(name);
	while (i < (int)ft_strlen(temp))
		temp[i] = '\0';
	while (len > 0)
	{
		str++;
		len--;
	}
	free(name);
	return (str);
}
