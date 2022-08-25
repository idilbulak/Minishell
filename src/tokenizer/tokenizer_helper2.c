/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_helper2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 20:48:54 by ibulak        #+#    #+#                 */
/*   Updated: 2022/08/25 20:49:45 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenizer.h"

char	*ft_rearrange(char *temp_str, int len)
{
	int	count;

	count = 0;
	while (count < len -1)
	{
		temp_str++;
		count++;
	}
	return (temp_str);
}

int	check_len(char *temp_str, int len)
{
	if (temp_str[len - 1] == ' ')
		len = len - 1;
	return (len);
}
