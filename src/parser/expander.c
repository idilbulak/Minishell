/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 20:57:02 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/25 21:16:48 by ibulak        ########   odam.nl         */
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

char	*fill_rest(char *temp, int i, char *str, char *name)
{
	int	len;

	len = ft_strlen(name);
	while (i < (int)ft_strlen(temp))
		temp[i] = '\0';
	while (len > 0)
	{
		str++;
		len--;
	}
	return (str);
}

char	*ft_expand(char *str, char *temp, t_symtab **symtab, int mode)
{
	char	*name;
	int		i;

	i = 0;
	while (*str != '\0')
	{
		mode = check_qmode(*str, mode);
		if (*str == '$' && (mode == 0 || mode == 2))
		{
			name = find_name(str);
			if (*name == '?' || symtab_lookup(symtab, name))
				i = expand_value(name, i, temp, symtab);
			else
				str = expand_helper(str, name);
			str = fill_rest(temp, i, str, name);
		}
		else if ((*str != '$' && (mode == 0 || mode == 2)) || mode == 1)
		{
			temp[i] = *str;
			i++;
		}
		str++;
	}
	temp[i] = '\0';
	return (temp);
}

int	ft_increase(char *str, int name_len, t_symtab **symtab )
{
	int	len;
	char	*temp;

	len = 0;
	temp = str;
	while (*temp != '$' && *temp != ' ' && *temp != '\'' && *temp != '"' && *temp != '\0')
	{
		len++;
		temp++;
	}
	char	*name = ft_substr(str, 0, len);
	char *value = NULL;
	if (symtab_lookup(symtab, name))
	{
		value = symtab_lookup(symtab, name)->value;
		name_len += ft_strlen(value);
		// free(value);
	}
	if (!symtab_lookup(symtab, name))
		name_len += 1;
	else if (ft_strcmp(name, "?"))
		name_len += 3;
	// free(value);
	free(name);
	return(name_len);
}

int	find_len(char *str, t_symtab **symtab)
{
	char	*temp;
	int		yes;
	int		len;

	yes = 0;
	temp = str;
	while(*temp)
	{
		if (*temp == '$')
			yes = 1;
		temp++;
	}
	temp = str;
	if (yes == 0)
	{
		len = ft_strlen(str);
	}
	else
	{
		int count = 0; //dolardan sonra dolarla beraber kac tane oldugu
		int name_len = 0; //name_len dolarsiz 
		while (*temp)
		{
			// printf("%s\n", temp);
			if (*temp == '$')
			{
				temp++;
				name_len = ft_increase(temp, name_len, symtab);
				count++;
				while (*temp != '$' && *temp != ' ' && *temp != '\'' && *temp != '"' && *temp != '\0')
				{
					count++;
					temp++;
				}
			}
			// printf(">>%s\n", temp);
			if(*temp != '\0' && *temp != '$')
				temp++;
		}
		len = ft_strlen(str) - count + name_len;
	}
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
			temp = malloc(sizeof(char) * len);
			mode = 0;
			temp = ft_expand(word_list->word->word, temp, symtab, mode);
			free(word_list->word->word);
			word_list->word->word = temp;
		}
		word_list = word_list->next;
	}
}
