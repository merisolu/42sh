/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:10:58 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/03 13:44:18 by jumanner         ###   ########.fr       */
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

static char	*parse_expansion(char *expansion, int index)
{
	size_t	length;
	char	*end_chars;

	length = 0;
	end_chars = " \t\n'\"";
	while (!ft_strchr(end_chars, expansion[index + length])
		&& expansion[index + length])
		length++;
	return (ft_strndup(expansion + index, length));
}

static int	find_expansion(char *input, int index)
{
	int		cursor;
	char	*end_chars;

	end_chars = " \t\n'\"";
	cursor = index;
	while (input[cursor])
	{
		if (input[cursor] != '!')
		{
			cursor++;
			continue ;
		}
		if (!ft_strchr(end_chars, input[cursor]) && input[cursor + 1] != '\0'
			&& !is_history_expansion_inhibited(input, cursor))
			return (cursor);
		else
			cursor++;
	}
	return (-1);
}

static bool	apply_expansion(char *target, int *cursor, t_state *state)
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
	*cursor = find_expansion(
			state->input_context.input, *cursor + ft_strlen(target) + 1);
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
	int		cursor;

	cursor = find_expansion(state->input_context.input, 0);
	if (cursor == -1)
		return (0);
	while (cursor > 0 && state->input_context.input[cursor])
	{
		target = parse_expansion(state->input_context.input, cursor);
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
