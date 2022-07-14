/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 10:54:51 by ibulak        #+#    #+#                 */
/*   Updated: 2022/07/06 10:54:52 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/tokenizer.h"

int	ft_isdigit(int c)
{
	if (!(c >= 48 && c <= 57))
		return (0);
	else
		return (1);
}

size_t	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (!(s[n] == '\0'))
		n++;
	return (n);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	x;
	size_t	len_s;

	if (!s)
		return (NULL);
	if ((ft_strlen((char *)s) < len))
		len = ft_strlen((char *)s);
	substr = (char *)malloc(sizeof(*s) * (len + 1));
	if (!substr)
		return (NULL);
	x = 0;
	len_s = ft_strlen((char *)s);
	if (start + x < len_s)
	{
		while (*(s + start) != '\0' && x < len)
		{
			*(substr + x) = *(s + start + x);
			x++;
		}
	}
	*(substr + x) = '\0';
	return (substr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	if (n == 0)
		return (0);
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0' && x < n - 1)
	{
		if (s1[x] != s2[x])
			break ;
		x++;
	}
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}

static int	ft_word_count(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_word_size(const char *s, int i, char c)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i] != '\0')
	{
		size++;
		i++;
	}
	return (size);
}

static int	ft_skip(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

static char	**ft_delete(char **s1, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(s1[i]);
		i++;
	}
	free(s1);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**s1;
	int		word_count;
	int		word_size;
	int		index_s1;
	int		i;

	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	s1 = (char **)malloc(sizeof(s) * (word_count + 1));
	if (!s1)
		return (NULL);
	index_s1 = 0;
	while (index_s1 < word_count)
	{
		i = ft_skip(s, c);
		word_size = ft_word_size(s, i, c);
		s1[index_s1] = ft_substr(s + i, 0, word_size);
		if (!s1[index_s1])
			return (ft_delete(s1, index_s1));
		index_s1++;
		s = s + i + word_size;
	}
	s1[index_s1] = NULL;
	return (s1);
}