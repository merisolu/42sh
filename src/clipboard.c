/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:21:42 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/07 10:26:30 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_input_result	cut_word(t_state *state)
{
	size_t	len;
	size_t	end;
	size_t	start;

	if (!(ft_strlen(state->input) > 0 && state->cursor > 0))
		return (NO_NEWLINE_FOUND);
	len = ft_strlen(state->input);
	end = state->cursor - 1;
	start = end;
	while (start > 0 && start < len && ft_is_whitespace(state->input[start]))
		start--;
	while (start > 0 && start < len && !ft_is_whitespace(state->input[start]))
		start--;
	if (start > 0)
		start++;
	ft_strncpy(state->clipboard, state->input + start, end - start + 1);
	state->clipboard[end - start + 1] = '\0';
	ft_strncpy(state->input, state->input, start);
	ft_strcpy(state->input + start, state->input + end + 1);
	ft_bzero(state->input + ft_strlen(state->input),
		INPUT_MAX_SIZE - ft_strlen(state->input));
	state->cursor -= end - start + 1;
	return (NO_NEWLINE_FOUND);
}

t_input_result	cut_to_cursor(t_state *state)
{
	ft_strncpy(state->clipboard, state->input, state->cursor);
	ft_strcpy(state->input, state->input + state->cursor);
	ft_bzero(state->input + ft_strlen(state->input),
		INPUT_MAX_SIZE - state->cursor);
	state->cursor = 0;
	return (NO_NEWLINE_FOUND);
}

t_input_result	cut_from_cursor(t_state *state)
{
	ft_strncpy(state->clipboard, state->input + state->cursor,
		ft_strlen(state->input + state->cursor));
	ft_bzero(state->input + state->cursor,
		ft_strlen(state->input) - state->cursor);
	return (NO_NEWLINE_FOUND);
}

t_input_result	paste(t_state *state)
{
	int	limit_reached;

	limit_reached = ft_strlen(state->input) + ft_strlen(state->clipboard)
		>= INPUT_MAX_SIZE;
	if (limit_reached)
		state->clipboard[INPUT_MAX_SIZE - ft_strlen(state->input)] = '\0';
	ft_memmove(
		state->input + state->cursor + ft_strlen(state->clipboard),
		state->input + state->cursor,
		ft_strlen(state->clipboard));
	ft_memcpy(state->input + state->cursor, state->clipboard,
		ft_strlen(state->clipboard));
	state->cursor += ft_strlen(state->clipboard);
	if (limit_reached)
	{
		ft_putstr(tgetstr("bl", NULL));
		ft_putstr(tgetstr("vb", NULL));
	}
	return (NO_NEWLINE_FOUND);
}
