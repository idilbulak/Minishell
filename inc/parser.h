#ifndef PARSER_H
# define PARSER_H

#include "tokenizer.h"
#include "environment.h"

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
t_word_list	*parser(t_token *tokens, t_symtab **symtab);
t_word_list	*parse_string(t_token *tokens, t_word_list *word_list);
char	*parse_string_helper(char *str, t_word_list *word_list);

//parser helper
void	ft_split_quotes(t_word_list *word_list);
void	adjust_wordlist(t_word_list *word_list);
void	check_env(t_word_list *word_list);
int	check_qmode(char str, int mode);
void	ft_expander(t_word_list *word_list, t_symtab **symtab);

// word_list utils
t_word_list	*init_word_list(t_word_list *word_list);
t_word_list	*init_new_word(t_word_list *new_word, t_token *tokens);
t_word_list	*addto_wend(t_word_list *head, t_word_list *new);
t_word_list	*addto_empty_wlist(t_word_list *head, t_word_list *new);
t_word_list	*init_new_str(t_word_list *new_word, char *new_str);
void	print_wordlist(t_word_list *word_list);

//checks
int	parser_checks(t_token *tokens);

void	var_assignment(t_word_list *word_list, t_symtab **symtab);
void	ft_expander(t_word_list *word_list, t_symtab **symtab);

#endif
