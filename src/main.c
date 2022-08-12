/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:25:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/11 13:23:02 by daansaat      ########   odam.nl         */
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

void	print_table(t_symtab **symtab)
{
	int	        i;
	t_symtab    *tmp;

	i = 0;
	while (i < TABLE_SIZE)
	{
		if (symtab[i] == NULL)
			printf("%d\t------\n", i);
		else
		{
			tmp = symtab[i];
			printf("%d\t", i);
			while (tmp != NULL)
			{
				printf("%s:%s || ", tmp->name, tmp->value);
				tmp = tmp->next;
			}
			printf("\n");
		}
		i++;
	}
}

void	var_assignment(t_word_list *word_list, t_symtab **symtab)
{
	t_symtab	*entry;

	while(word_list)
	{
		if (word_list->word->flags == TOKEN_ENV)
		{
			entry = new_entry(word_list->word->word);
			if(symtab_lookup(symtab, entry->name))
				symtab_delete(symtab, entry->name);
			symtab_insert(symtab, entry);
		}
		word_list = word_list->next;
	}
}

char	*find_value(char *str)
{
	int	i;
	char	*value;

	i = 0;
	value = malloc(sizeof(char));
	str++;
	while(*str != '$' && *str != '\0')
	{
		value[i] = *str;
		i++;
		str++;
	}
	return (value);
}

void	ft_expander(t_word_list *word_list, t_symtab **symtab)
{
	char	*str;
	char	*temp;
	char	*value;
	int		mode;
	int		i;
	int		j;

	while (word_list)
	{
		mode = 0;
		temp = malloc(sizeof(char ));
		if (word_list->word->flags == TOKEN_STRING)
		{
			str = word_list->word->word;
			i = 0;
			while (*str != '\0')
			{
				mode = check_qmode(*str, mode);
				j = 0;
				if (*str == '$' && (mode == 0 || mode == 2))
				{
					value = find_value(str);
					printf("valueeee: %s\n", value);
					value = symtab_lookup(symtab, value)->value;
					printf("valueeee: %s\n", value);
					while (value[j] != '\0')
					{
						temp[i] = value[j];
						i++;
						j++;
					}
					str++;
					while(*str != '$' && *str != ' ' && *str != '\0')
						str++;
				}
				if (*str != '$')
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

int	main(int argc, char **argv, char **environ)
{
	int         exit_code;
    char		*str;
	t_token		*tokens;
	t_word_list	*word_list;
	t_symtab	**symtab;

	(void)argc;
	(void)argv;
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
		print_tokens(tokens);
		word_list = parser(tokens, symtab);
		print_wordlist(word_list);
		var_assignment(word_list, symtab);
		print_table(symtab);
		exit_code = executor(word_list, symtab);
        printf("exit_code = %d\n", exit_code);
		free(str);
		free(tokens);
		free(word_list);
		// str = NULL;
		// printf("ïf no seg faults, say YEAYYY!\n");
	}
}

// gcc -lreadline main.c
// HISTORY_STATE *myhist = history_get_history_state ();