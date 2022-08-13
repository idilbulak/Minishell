#include "../../inc/parser.h"

int	name_len(char *str)
{
	int	count;

	count = 0;
	while (*str != '$' && *str != '\0')
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
	int	len;
	int	i;
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

char	*find_value(char *name, t_symtab **symtab)
{
	char	*value;

	value = symtab_lookup(symtab, name)->value;
	return (value);
}

void	ft_expander(t_word_list *word_list, t_symtab **symtab)
{
	char	*str;
	char	*temp;
	char	*name;
	char	*value;
	int		mode;
	int		i;
	int		j;
	int		len;

	while (word_list)
	{
		mode = 0;
		temp = malloc(sizeof(char *));
		if (word_list->word->flags == TOKEN_STRING)
		{
			str = word_list->word->word;
			i = 0;
			while (*str != '\0')
			{
				mode = check_qmode(*str, mode);
				j = 0;
				if (*str == '$' && (mode == 0 || mode == 2))
				{
					name= find_name(str);
                    if (*name == '?')
					{
						value = ft_itoa(g_exit_code);
						while (value[j] != '\0')
                        {
                            temp[i] = value[j];
                            i++;
                            j++;
                        }
					}
					else if (symtab_lookup(symtab, name))
					{
						value = find_value(name, symtab);
						while (value[j] != '\0')
                        {
                            temp[i] = value[j];
                            i++;
                            j++;
                        }
					}
					len = ft_strlen(name);
					while(len > 0)
					{
						str++;
						len--;
					}
					if (value != NULL)
						free (value);
					free (name);
				}
				else if (*str != '$')
				{
					temp[i] = *str;
					i++;
				}
				str++;
			}
			free(word_list->word->word);
			word_list->word->word = temp;
			// free(str);
		}
		word_list = word_list->next;
	}
}