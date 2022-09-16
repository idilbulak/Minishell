/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:55:38 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/16 12:30:55 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "environment.h"

typedef enum e_tokentype
{
	TOKEN_null,
	TOKEN_PIPE,
	TOKEN_GREATER,
	TOKEN_LESS,
	TOKEN_DOUBLEGREATER,
	TOKEN_DOUBLELESS,
	TOKEN_STRING,
	TOKEN_FILEPATH,
	TOKEN_ENV,
	TOKEN_CENV
}	t_tokentype;

typedef struct s_token
{
	char			*data;
	t_tokentype		tokentype;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// tokenizer
bool		if_endofdata(char *str, bool state);
char		*find_startofdata(char *str);
char		*find_startoftoken(char *str);
t_token		*tokenizer(char *line, t_token *tokens);

// tokenizer helper
char		*find_delimiter( char *str, t_token *new_token);
char		*find_char(char *str, t_token *new_token, int len, char *temp_str);
char		*typeoftoken(char *str, t_token *new_token);

// tokenizer helper 2
char		*ft_rearrange(char *temp_str, int len);
int			check_len(char *temp_str, int len);
t_token		*error_unclosed(t_token *tokens);

// tokenizer checks
int			check_ifpath(t_token *tokens);
int			check_ifredirection(t_token *tokens);
int			check_unclosedquotes(char *str);

// tokenlist_utils
t_token		*init_token(t_token *token);
t_token		*addto_emptylist(t_token *tokens, t_token *new);
t_token		*addto_end(t_token *tokens, t_token *new);
void		free_tokens(t_token *tokens);
void		print_tokens(t_token *head);

#endif