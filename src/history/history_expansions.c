/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:10:58 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/02 14:36:11 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	expansion_to_history_index(char *expansion, t_state *state)
{
	char	*start;
	int		result;

	start = expansion + 1;
	if (ft_strequ(start, "!"))
		result = 1;
	else if (ft_isdigit_str(start))
		result = history_number_to_index(ft_atoi(start), state);
	else if (*start == '-' && ft_isdigit_str(start + 1))
		result = history_number_to_index(
				get_history_length(state) - ft_atoi(start + 1) + 1, state);
	else
		result = history_seek(state, 0, start, false);
	if (result <= 0 || result >= get_history_length(state))
	{
		ft_putchar('\n');
		return (print_error(-1,
				ERRTEMPLATE_NAMED, expansion, "event not found"));
	}
	return (result);
}

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

static bool	apply_expansion(char *target, char **cursor, t_state *state)
{
	char	*temp;
	int		index;

	index = expansion_to_history_index(target, state);
	if (index == -1)
		return (false);
	temp = ft_strreplace(state->input_context.input, target,
			state->history[index]);
	if (!temp)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	ft_strncpy(state->input_context.input, temp, INPUT_MAX_SIZE);
	*cursor = find_expansion(*cursor + ft_strlen(target) + 1);
	free(temp);
	return (true);
}

/* 
 * Applies history expansions to the input context in *state. Returns 0 if no
 * expansions were applied, 1 if they were, -1 on error.
 */
int	history_expand(t_state *state)
{
	char	*target;
	char	*cursor;

	cursor = find_expansion(state->input_context.input);
	if (!cursor)
		return (0);
	while (cursor)
	{
		target = parse_expansion(cursor);
		if (!target)
			return (print_error_bool(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		if (!apply_expansion(target, &cursor, state))
		{
			free(target);
			return (-1);
		}
		free(target);
	}
	return (1);
}
