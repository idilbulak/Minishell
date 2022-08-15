/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/14 20:57:02 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/14 21:00:27 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	name_len(char *str)
{
	int	count;

	count = 0;
	while (*str != '$' && *str != '\0' && *str != '"')
	{
		if (*str == '?')
			return (1);
		count++;
		str++;
	}
	return (count);
}

char	*find_name(char *str)
{
	int		len;
	int		i;
	char	*name;

	str++;
	i = 0;
	len = name_len(str);
	name = malloc(sizeof(char *) * len);
	while (len > 0)
	{
		name[i] = *str;
		i++;
		str++;
		len--;
	}
	return (name);
}

// char	*find_value(char *name, t_symtab **symtab)
// {
// 	char	*value;

// 	value = symtab_lookup(symtab, name)->value;
// 	return (value);
// }

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

	if (*str == '"')
		str++;
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

char	*ft_expand(char *str, char *temp, t_symtab **symtab)
{
	char	*name;
	int		mode;
	int		i;

	i = 0;
	while (*str != '\0')
	{
		mode = check_qmode(*str, mode);
		if (*str == '$' && (mode == 0 || mode == 2))
		{
			name= find_name(str);
            if (*name == '?' || symtab_lookup(symtab, name))
				i = expand_value(name, i, temp, symtab);
			else
			{
				while(*str != '$')
					str++;
				free(name);
			}
			str = fill_rest(temp, i, str, name);
		}
		else if ((*str != '$' && (mode == 0 || mode == 2)) || mode == 1)
		{
			temp[i] = *str;
			i++;
		}
		str++;
	}
	return (temp);
}
void	ft_expander(t_word_list *word_list, t_symtab **symtab)
{
	char	*temp;

	while (word_list)
	{
		temp = malloc(sizeof(char *));
		if (word_list->word->flags == TOKEN_STRING)
		{
			temp = ft_expand(word_list->word->word, temp, symtab);
			free(word_list->word->word);
			word_list->word->word = temp;
		}
		word_list = word_list->next;
	}
}

// int	name_len(char *str)
// {
// 	int	count;

// 	count = 0;
// 	while (*str != '$' && *str != '\0' && *str != '"')
// 	{
// 		if (*str == '?')
// 			return (1);
// 		count++;
// 		str++;
// 	}
// 	return (count);
// }

// char	*find_name(char *str)
// {
// 	int		len;
// 	int		i;
// 	char	*name;

// 	str++;
// 	i = 0;
// 	len = name_len(str);
// 	name = malloc(sizeof(char *) * len);
// 	while (len > 0)
// 	{
// 		name[i] = *str;
// 		i++;
// 		str++;
// 		len--;
// 	}
// 	return (name);
// }

// char	*find_value(char *name, t_symtab **symtab)
// {
// 	char	*value;

// 	value = symtab_lookup(symtab, name)->value;
// 	return (value);
// }

// void	ft_expander(t_word_list *word_list, t_symtab **symtab)
// {
// 	char	*str;
// 	char	*temp;
// 	char	*name;
// 	char	*value;
// 	int		mode;
// 	int		i;
// 	int		j;
// 	int		len;

// 	while (word_list)
// 	{
// 		mode = 0;
// 		temp = malloc(sizeof(char *));
// 		if (word_list->word->flags == TOKEN_STRING)
// 		{
// 			str = word_list->word->word;
// 			i = 0;
// 			while (*str != '\0')
// 			{
// 				mode = check_qmode(*str, mode);
// 				j = 0;
// 				if (*str == '$' && (mode == 0 || mode == 2))
// 				{
// 					name= find_name(str);
// 					// printf("name:%s\n",name);
// 					// printf("str:%s\n",str);
//                     if (*name == '?')
// 					{
// 						value = ft_itoa(g_exit_code);
// 						while (value[j] != '\0')
//                         {
//                             temp[i] = value[j];
//                             i++;
//                             j++;
//                         }
// 						free (value);
// 						free (name);
// 					}
// 					else if (symtab_lookup(symtab, name))
// 					{
// 						value = symtab_lookup(symtab, name)->value;
// 						while (value[j] != '\0')
//                         {
//                             temp[i] = value[j];
//                             i++;
//                             j++;
//                         }
// 						free (name);
// 					}
// 					else
// 					{
// 						while(*str != '$')
// 							str++;
// 						free(name);
// 					}
// 					len = ft_strlen(name);
// 					while (i < (int)ft_strlen(temp))
// 						temp[i] = '\0';
// 					while (len > 0)
// 					{
// 						str++;
// 						len--;
// 					}
// 				}
// 				else if ((*str != '$' && (mode == 0 || mode == 2)) || mode == 1)
// 				{
// 					temp[i] = *str;
// 					i++;
// 				}
// 				str++;
// 			}
// 			free(word_list->word->word);
// 			word_list->word->word = temp;
// 		}
// 		word_list = word_list->next;
// 	}
// }
