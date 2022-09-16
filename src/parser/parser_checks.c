/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/13 13:44:20 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/16 09:56:02 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/minishell.h"

int	parser_check_helper(t_token *t)
{
	if (t->next == NULL)
		return (-2);
	else if (check_ifredirection(t->next))
		return (-3);
	else if (t->next->tokentype == TOKEN_PIPE
		|| check_ifredirection(t->next))
		return (-1);
	return (0);
}

int	parser_checks(t_token *t)
{
	while (t)
	{
		if (t->tokentype == TOKEN_PIPE)
		{
			if (t->prev == NULL)
				return (-1);
			else if (t->next == NULL || t->next->tokentype == TOKEN_PIPE)
				return (-1);
		}
		else if (check_ifredirection(t) == 1)
		{
			if (parser_check_helper(t))
				return (parser_check_helper(t));
		}
		t = t->next;
	}
	return (1);
}

void	syntax_error(int e)
{
	if (e == -1)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (e == -2)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline' \
		\n", 2);
	else if (e == -3)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
}

int	count_words(char **words)
{
	int	count;

	count = 0;
	while (words[count])
		count++;
	return (count);
}

// enum e_tokentype	chose_flag(char *str)
// {
	// if (!ft_strcmp(str, "|"))
	// 	return (TOKEN_PIPE);
	// else if (!ft_strcmp(str, ">"))
	// 	return (TOKEN_GREATER);
	// else if (!ft_strcmp(str, ">>"))
	// 	return (TOKEN_DOUBLEGREATER);
	// else if (!ft_strcmp(str, "<"))
	// 	return (TOKEN_LESS);
	// else if (!ft_strcmp(str, "<<"))
	// 	return (TOKEN_DOUBLELESS);
	// else if (ft_strchr(str, '='))
	// 	return (TOKEN_ENV);
	// else
	// 	return (TOKEN_STRING);
// }

// t_word_list	*split_words(t_word_list *word_list, char *word)
// {
	// t_word_list	*temp;
	// char		**words;
	// t_word_list	*new_word;
	// int			count;
	// int			i;

	// temp = word_list;
	// while (temp->next)
	// {
	// 	new_word = NULL;
	// 	if (temp->word->word == word)
	// 	{
	// 		words = ft_split(word, ' ');
	// 		count = count_words(words);
	// 		i = 1;
	// 		free(temp->word->word);
	// 		temp->word->word = words[0];
	// 		temp->word->flags = TOKEN_STRING;
	// 		while (i < count)
	// 		{
	// 			new_word = init_new_word(new_word);
	// 			new_word->word->word = words[i];
	// 			new_word->word->flags = TOKEN_STRING;
	// 			if (temp->next == NULL)
	// 			{
	// 				word_list = addto_wend(word_list, new_word);
	// 				temp = temp->next;
	// 			}
	// 			// // else
	// 			// // {
	// 			// 	new_word->next = temp->next;
	// 			// 	temp->next = new_word;
	// 			// // }
	// 			i++;
	// 		}
	// 		free (words);
	// 	}
	// 	temp = temp->next;
	// }
	// // word_list = temp;
	// return (word_list);
// }

// t_word_list	*expand_check(t_word_list *word_list)
// {
	// char		*str;
	// int			i;
	// int			mode;
	// t_word_list	*temp;

	// str = NULL;
	// i = 0;
	// mode = 0;
	// temp = word_list;
	// while (temp->next)
	// {
	// 	str = temp->word->word;
	// 	if (temp->word->flags == TOKEN_STRING)
	// 	{
	// 		while (str[i])
	// 		{
	// 			mode = check_qmode(str[i], mode);
	// 			if (mode != 1 && str[i] == ' ')//???????????????????
	// 			{
	// 				word_list = split_words(word_list, temp->word->word);
	// 				break ;
	// 			}
	// 			i++;
	// 		}
	// 	}
	// 	temp = temp->next;
	// }
	// // free(temp);
	// return (word_list);
// }

// t_token	*pipe_without_next(t_token *tokens)
// {
// 	char	*str;
// 	t_token	*new_token;

// 	str = readline("> ");
// 	if (!str)
// 	{
// 		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
// 		g_exit_code = 258;
// 		str = NULL;
// 		return (tokens);
// 	}
// 	new_token = NULL;
// 	new_token = init_token(new_token);
// 	new_token->tokentype = TOKEN_STRING;
// 	new_token->data = str;
// 	tokens->next = new_token;
// 	return (tokens);
// }

// t_token	*twopipes_without_next(t_token *tokens)
// {
// 	char	*str;

// 	str = readline("> ");
// 	if (!str)
// 	{
// 		ft_putstr_fd("\b minishell: syntax error: unexpected end of file\n", 2);
// 		g_exit_code = 258;
// 		str = NULL;
// 		return (tokens);
// 	}
// 	tokens = tokens->prev;
// 	free(tokens->next->next->data);
// 	free(tokens->next->next);
// 	free(tokens->next->data);
// 	free(tokens->next);
// 	tokens->next = NULL;
// 	free(str);
// 	str = NULL;
// 	return (tokens);
// }

// int	parser_checks(t_token *t)
// {
// 	while (t)
// 	{
// 		if (t->tokentype == TOKEN_PIPE)
// 		{
// 			if (t->prev == NULL)
// 				return (-1);
// 			else if (t->next == NULL)
// 				t = pipe_without_next(t);
// 			else if (t->next->tokentype == TOKEN_PIPE && t->next->next == NULL)
// 				t = twopipes_without_next(t);
// 			else if (t->next->tokentype == TOKEN_PIPE
// 				&& t->next->next->tokentype == TOKEN_PIPE)
// 				return (-1);
// 		}
// 		else if (check_ifredirection(t) == 1)
// 		{
// 			if (parser_check_helper(t))
// 				return (parser_check_helper(t));
// 		}
// 		t = t->next;
// 	}
// 	return (1);
// }