#include "../../inc/parser.h"

char	*find_value(char *str)
{
	int	i;
	char	*value;

	i = 0;
	value = malloc(sizeof(char));
	str++;
	while(*str != '$' && *str != '\0')
	{
		value[i] = *str;
		i++;
		str++;
	}
	return (value);
}

void	ft_expander(t_word_list *word_list, t_symtab **symtab)
{
	char	*str;
	char	*temp;
	char	*value;
	int		mode;
	int		i;
	int		j;

	while (word_list)
	{
		mode = 0;
		temp = malloc(sizeof(char ));
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
					value = find_value(str);
					printf("valueeee: %s\n", value);
					value = symtab_lookup(symtab, value)->value;
					printf("valueeee: %s\n", value);
					while (value[j] != '\0')
					{
						temp[i] = value[j];
						i++;
						j++;
					}
					str++;
					while(*str != '$' && *str != ' ' && *str != '\0')
						str++;
				}
				if (*str != '$')
				{
					temp[i] = *str;
					i++;
				}
				str++;
			}
			word_list->word->word = temp;
		}
		word_list = word_list->next;
	}
}