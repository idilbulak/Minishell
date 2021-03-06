#ifndef PARSER_H
# define PARSER_H

#include "tokenizer.h"

typedef struct s_word_desc
{
	char		*word;
	t_tokentype	flags;
}	t_word_desc;

typedef struct s_word_list
{
	struct s_word_list	*next;
	t_word_desc	*word;
}	t_word_list;

// parser
t_word_list	*parser(t_token *tokens);

// word_list utils
t_word_list	*init_word_list(t_word_list *word_list);
t_word_list	*init_new_word(t_word_list *new_word, t_token *tokens);
t_word_list	*addto_wend(t_word_list *head, t_word_list *new);
t_word_list	*addto_empty_wlist(t_word_list *head, t_word_list *new);
void	print_wordlist(t_word_list *word_list);

//checks
int	parser_checks(t_token *tokens);

#endif
