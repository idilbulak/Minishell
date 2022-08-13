/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 17:12:49 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/13 16:15:37 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include "environment.h"

typedef struct s_word_desc
{
	char				*word;
	t_tokentype			flags;
}	t_word_desc;

typedef struct s_word_list
{
	struct s_word_list	*next;
	t_word_desc			*word;
}	t_word_list;

// parser
t_word_list	*parser(t_token *tokens, t_symtab **symtab);
t_word_list	*create_word_list(t_token *tokens, t_word_list *word_list);
t_word_list	*parse_string(char *str, t_word_list *word_list);
int			parse_string_helper(char *str, int len);
void		var_assignment(t_word_list *word_list, t_symtab **symtab);

//parser helper
void		adjust_wordlist(t_word_list *word_list);
void		check_env(t_word_list *word_list);

//quote remover
void		ft_split_quotes(t_word_list *word_list);
int			check_qmode(char str, int mode);

//expander
void		ft_expander(t_word_list *word_list, t_symtab **symtab);

// word_list utils
t_word_list	*init_new_word(t_word_list *new_word);
t_word_list	*addto_wend(t_word_list *head, t_word_list *new);
t_word_list	*addto_empty_wlist(t_word_list *head, t_word_list *new);
void		free_word_list(t_word_list *word_list);
void		print_wordlist(t_word_list *word_list);

//checks
int			parser_checks(t_token *tokens);

#endif
