/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 20:57:02 by ibulak        #+#    #+#                 */
/*   Updated: 2022/09/14 10:53:32 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	expand_value(char *name, int i, char *temp, t_symtab **symtab)
{
	int		j;
	char	*value;

	j = 0;
	if (*name == '?')
		value = ft_itoa(g_exit_code);
	else
		value = symtab_lookup(symtab, name)->value;
	while (value[j] != '\0')
	{
		temp[i] = value[j];
		i++;
		j++;
	}
	if (*name == '?')
		free (value);
	free (name);
	return (i);
}

char	*ft_expand(char *str, char *temp, t_symtab **symtab, int mode)
{
	char	*name;
	int		i;

	i = 0;
	while (*str != '\0')
	{
		mode = check_qmode(*str, mode);
		if (*str == '$' && (*(str + 1) == ' ' || *(str + 1) == '\0'
				|| *(str + 1) == '/' || *(str + 1) == '%' || *(str + 1) == '+'
				|| *(str + 1) == ',' || *(str + 1) == '='
				|| *(str + 1) == ':' || *(str + 1) == '.'))
			temp[i++] = '$';
		else if (*str == '$' && (mode == 0 || mode == 2))
		{
			name = find_name(str);
			if (*name == '?' || symtab_lookup(symtab, name))
				i = expand_value(name, i, temp, symtab);
			else
				str = expand_helper(str, name);
			name = find_name(str);
			str = fill_rest(temp, i, str, name);
		}
		else
			temp[i++] = *str;
		str++;
	}
	temp[i] = '\0';
	return (temp);
}

int	if_dollar(char *str)
{
	char	*temp;
	int		yes;

	yes = 0;
	temp = str;
	while (*temp)
	{
		if (*temp == '$')
			yes = 1;
		temp++;
	}
	return (yes);
}

int	find_len(char *str, t_symtab **symtab)
{
	char	*temp;
	int		len;
	int		mode;

	temp = str;
	len = 0;
	mode = 0;
	mode = check_qmode(*str, mode);
	if (if_dollar(temp) == 0 || mode == 1)
		len = ft_strlen(str);
	else
		len = ft_strlen(str) + calculate_new_len(len, symtab, temp);
	return (len);
}

void	ft_expander(t_word_list *word_list, t_symtab **symtab)
{
	char	*temp;
	int		mode;
	int		len;

	while (word_list)
	{
		if (word_list->word->flags == TOKEN_STRING)
		{
			len = find_len(word_list->word->word, symtab);
			temp = malloc(sizeof(char) * (len + 3));
			if (!temp)
				ft_error(EXIT_FAILURE, "malloc failed");
			mode = 0;
			temp = ft_expand(word_list->word->word, temp, symtab, mode);
			free(word_list->word->word);
			word_list->word->word = temp;
		}
		word_list = word_list->next;
	}
}
