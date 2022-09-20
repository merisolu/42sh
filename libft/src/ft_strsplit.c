/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:08:15 by jumanner          #+#    #+#             */
/*   Updated: 2022/08/26 14:50:34 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the distance to char c in string s. */
static int	dist_to_sep(const char *s, char c)
{
	int	result;

	if (!s)
		return (0);
	result = 0;
	while (s[result] && s[result] != c)
		result++;
	return (result);
}

/* Get the word count in string s, using char c as the separator between
 * words. */
static int	get_word_count(char const *s, char c)
{
	char	*cursor;
	int		words;

	cursor = (char *)s;
	words = 0;
	while (cursor)
	{
		while (cursor && *cursor == c)
			cursor++;
		if (dist_to_sep(cursor, c) > 0)
			words++;
		cursor = ft_strchr(cursor, c);
	}
	return (words);
}

/* Splits the string s by using char c as the separator between words. The end
 * result is a null terminated array with each word having its own element
 * inside the array. */
char	**ft_strsplit(char const *s, char c)
{
	char	**result;
	char	*cursor;
	int		words;
	int		i;

	words = get_word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	cursor = (char *)s;
	i = 0;
	while (i < words)
	{
		while (*cursor == c && cursor)
			cursor++;
		result[i] = (char *)malloc(sizeof(char) * dist_to_sep(cursor, c) + 1);
		if (!result[i])
			return (((char **)ft_free_array((void **)result, words)));
		ft_memcpy(result[i], cursor, dist_to_sep(cursor, c));
		result[i][dist_to_sep(cursor, c)] = '\0';
		cursor = ft_strchr(cursor + 1, c);
		i++;
	}
	result[words] = NULL;
	return (result);
}
