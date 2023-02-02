/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:10:58 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/02 12:35:32 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static char	*parse_expansion(char *expansion)
{
	size_t	length;

	length = 0;
	while (!ft_is_whitespace(expansion[length]) && expansion[length])
		length++;
	return (ft_strndup(expansion, length));
}

static char	*find_expansion(char *input)
{
	char	*cursor;

	cursor = input;
	while (*cursor)
	{
		if (*cursor != '!')
		{
			cursor++;
			continue ;
		}
		if (*cursor != ' ' && *cursor != '\t' && *cursor != '\n')
			return (cursor);
	}
	return (NULL);
}

/* 
 * Applies history expansions to the input context in *state. Returns 0 if no
 * expansions were applied, 1 if they were, and -1 on malloc error.
 */
int	history_expand(t_state *state)
{
	char	*temp;
	char	*target;
	char	*expansion;

	expansion = find_expansion(state->input_context.input);
	if (!expansion)
		return (0);
	while (expansion)
	{
		target = parse_expansion(expansion);
		if (!target)
			return (-1);
		temp = ft_strreplace(state->input_context.input, target,
				state->history[1]);
		if (!temp)
		{
			free(target);
			return (-1);
		}
		ft_strncpy(state->input_context.input, temp, INPUT_MAX_SIZE);
		expansion = find_expansion(expansion + ft_strlen(target) + 1);
		free(temp);
		free(target);
	}
	return (1);
}
