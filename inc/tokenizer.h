/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:55:38 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 11:05:46 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdio.h>
# include <stdlib.h>

typedef enum e_state
{
	STATE_FindStartOfData,
	STATE_FindStartOfToken,
	STATE_ParseQuotedString,
	STATE_ParseUnquotedString,
	STATE_ParseNumber,
	STATE_FindDelimiter,
	STATE_CheckEndOfString,
	STATE_ParseError,
	STATE_EndOfData
}	t_state;

typedef enum e_tokentype
{
	TOKEN_null, //0
	TOKEN_PIPE, //1
	TOKEN_GREATER, //2
	TOKEN_LESS, //3
	TOKEN_DOUBLEGREATER, //4
	TOKEN_DOUBLELESS, //5
	TOKEN_STRING,  //6
	// TOKEN_doubleQuotedString,
	// TOKEN_singleQuotedString,
	// TOKEN_unquotedString,
	TOKEN_FILEPATH //7
}	t_tokentype;

typedef struct s_token
{
	char				*data;
	t_tokentype			tokentype;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

// tokenizer
t_state		if_endofdata(char *str, t_state state);
char		*find_startofdata(char *str);
char		*find_startoftoken(char *str);
t_token		*tokenizer(char *line, t_token *tokens);

// tokenizer helper
char		*find_delimiter( char *str, t_token *new_token);
char		*parse_quotedstring( char *str, t_token *new_token);
char		*parse_unquotedstring(char *str, t_token *new_token);

// tokenizer helper2
char		*typeoftoken(char *str, t_token *new_token);
t_token		*find_path(t_token *tokens);
int			check_ifpath(t_token *tokens);
int			check_ifredirection(t_token *tokens);

// tokenlist_utils
t_token		*init_tokens(t_token *tokens);
t_token		*addto_emptylist(t_token *head, t_token *new);
t_token		*addto_end(t_token *head, t_token *new);
void		print_tokens(t_token *head);

// libft
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif