/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 17:12:49 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/16 12:15:26 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
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
void		check_validenv(t_word_list *word_list);
void		check_envorder(t_word_list *word_list);
char		*fill_rest(char *temp, int i, char *str, char *name);

// parser helper 2
char		*ft_helper(char *str, char *temp_str);
int			check_ifexpand(t_word_list *word_list);
int			check_null(t_token *tokens);
t_word_list	*create_null_list(t_word_list *word_list);
int			calculate_new_len(int name_len, int c, t_symtab **symtab, char *t);

//quote remover
void		ft_split_quotes(t_word_list *word_list);
int			check_qmode(char str, int mode);
int			expand_until(char temp);
int			check_char(char *str);

//expander
int			expand_value(char *name, int i, char *temp, t_symtab **symtab);
char		*ft_expand(char *str, char *temp, t_symtab **symtab, int mode);
int			if_dollar(char *str);
int			find_len(char *str, t_symtab **symtab);
void		ft_expander(t_word_list *word_list, t_symtab **symtab);

// expander helper
char		*expand_helper(char *str, char *name);
char		*find_name(char *str);
int			name_len(char *str);
int			ft_increase(char *str, int name_len, t_symtab **symtab);
int			find_name_len(int name_len, t_symtab **symtab, char *name);

// expander_heredoc
char		*ft_expand_heredoc(char *str, char *temp, t_symtab **symtab);
char		*ft_expander_heredoc(char *str, t_symtab **symtab);
// int			check_ifexpand_heredoc(char *str);

// word_list utils
t_word_list	*init_new_word(t_word_list *new_word);
t_word_list	*addto_wend(t_word_list *head, t_word_list *new);
t_word_list	*addto_empty_wlist(t_word_list *head, t_word_list *new);
void		free_word_list(t_word_list *word_list);
int			calculate_exit_code_len(void);
// void		print_wordlist(t_word_list *word_list);

//checks
int			parser_checks(t_token *tokens);
void		syntax_error(int e);
t_word_list	*expand_check(t_word_list *word_list);

#endif
