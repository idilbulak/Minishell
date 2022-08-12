#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/env.h"
#include <stdio.h>

#include "../../inc/exec.h"
#include "../../inc/tokenizer.h"
#include "../../inc/parser.h"
#include "../../inc/environment.h"
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

void	check_env(t_word_list *word_list)
{
	char	*str;
	int 	var;

	while (word_list)
	{
		if (word_list->word->flags == TOKEN_STRING)
		{
			str = word_list->word->word;
			var = 0;
			str++;
			while(*str != '\0')
			{
				if(*str == '=')
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

int	check_cenv(t_word_list *word_list)
{
	while(word_list->next)
	{
		if(word_list->word->flags == TOKEN_CENV)
			return(1);
		word_list = word_list->next;
	}
	return(0);
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
			if (word_list->next->word->flags != TOKEN_ENV && word_list->next->word->flags != TOKEN_null)
				word_list->word->flags = TOKEN_CENV;
		}
		word_list = word_list->next;
	}
}

void	adjust_wordlist(t_word_list *word_list)
{
	check_envorder(word_list);
	while (word_list->next)
	{
		if (word_list->word->flags == TOKEN_ENV)
		{
			if (word_list->next->word->flags == TOKEN_CENV)
				word_list->word->flags = TOKEN_CENV;
		}
		word_list = word_list->next;
	}
}

// void	ft_expander(t_word_list *word_list)
// {
// 	char	*str;
// 	char	*temp;
// 	char	*value;
// 	int		mode;
// 	int		i;
// 	int		j;

// 	while (word_list)
// 	{
// 		mode = 0;
// 		temp = malloc(sizeof(char ));
// 		if (word_list->word->flags == TOKEN_STRING)
// 		{
// 			str = word_list->word->word;
// 			i = 0;
// 			while (*str != '\0')
// 			{
// 				mode = check_qmode(*str, mode);
// 				if (*str == '$' && (mode == 0 && mode == 2))
// 				{
// 					str++;
// 					j = 0;
// 					while (*str != '$' && *str != ' ')
// 					{
// 						value = "lookup";
// 						temp[i] = value[j];
// 						j++;
// 						str++;
// 					}
// 				}
// 				temp[i] = *str;
// 				i++;
// 				str++;
// 			}
// 			word_list->word->word = temp;
// 		}
// 		word_list = word_list->next;
// 	}
// }

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
		    perror("malloc()");
		    exit(EXIT_FAILURE);
	    }
		if (word_list->word->flags == TOKEN_STRING)
		{
			str = word_list->word->word;
			i = 0;
			while (*str != '\0')
			{
				mode = check_qmode(*str, mode);
				if ((*str != '\'' || mode != 1) && (*str != '\'' || mode != 0) && (*str != '"' || mode != 2) && (*str != '"' || mode != 0))
				{
					temp[i] = *str;
					i++;
				}
				str++;
			}
			word_list->word->word = temp;
		}
		word_list = word_list->next;
	}
}