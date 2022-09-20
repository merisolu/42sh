/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:58:53 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:10:15 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns true if the given char is valid whitespace specified in the
 * libft PDF. */
static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/* Returns the index of the first non-whitespace character in string s,
 * starting from index start, going in direction dir. */
static int	get_non_ws_index(const char *s, int start, int dir)
{
	int	result;

	result = start;
	while (result + dir > 0 && s[result])
	{
		if (!is_whitespace(s[result]))
			break ;
		result += dir;
	}
	return (result);
}

/* Returns a copy of string s, with all of the whitespace at the start and end
 * of the string having been removed. */
char	*ft_strtrim(char const *s)
{
	char	*result;
	int		start;
	int		end;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	start = get_non_ws_index(s, 0, 1);
	end = get_non_ws_index(s, ft_strlen(s) - 1, -1);
	len = end - start + 1;
	if (len < 0)
		len = 0;
	result = (char *)malloc(sizeof(char) + len);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
