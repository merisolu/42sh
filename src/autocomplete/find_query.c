/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_query.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:54:23 by amann             #+#    #+#             */
/*   Updated: 2023/02/15 18:23:46 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static char	*find_query_loop(int len, char *str, char c)
{
	int	start;

	start = 0;
	while (len > -1)
	{
		if (str[len] == c)
		{
			start = len + 1;
			break ;
		}
		len--;
	}
	return (ft_strdup(str + start));
}

static bool	expansion_handler(t_state *state, char *last_word)
{
	bool	var;
	char	*temp;

	var = last_word[0] == '$';
	temp = ft_strdup(last_word);
	if (!temp)
	{
		free(last_word);
		return (false);
	}
	if (!expand_node(&temp, state, true))
	{
		free(temp);
		free(last_word);
		return (false);
	}
	if (var)
		insert_expansion(&(state->input_context), temp);
	free(temp);
	return (true);
}

char	*find_query(char *str, char c, t_state *state, bool expand)
{
	char	*last_word;
	char	*res;

	last_word = find_query_loop((int)ft_strlen(str), str, ' ');
	if (!last_word)
		return (NULL);
	if (expand)
	{
		if (!expansion_handler(state, last_word))
			return (NULL);
	}
	if (c == ' ')
		return (last_word);
	res = find_query_loop((int)ft_strlen(last_word), last_word, c);
	free(last_word);
	if (!res)
		return (NULL);
	return (res);
}
