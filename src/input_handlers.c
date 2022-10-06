/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:29:22 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/06 14:07:56 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_input_result	handle_newline(t_state *state)
{
	state->cursor = 0;
	return (NEWLINE_FOUND);
}

static t_input_result	handle_delete_word(t_state *state)
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
	ft_strncpy(state->input, state->input, start);
	ft_strcpy(state->input + start, state->input + end + 1);
	ft_bzero(state->input + ft_strlen(state->input),
		INPUT_MAX_SIZE - ft_strlen(state->input));
	state->cursor -= end - start + 1;
	return (NO_NEWLINE_FOUND);
}

static t_input_result	handle_delete_char(t_state *state)
{
	if (state->cursor == 0)
		return (NO_NEWLINE_FOUND);
	ft_strcpy(state->input + state->cursor - 1, state->input + state->cursor);
	ft_bzero(state->input + ft_strlen(state->input),
		INPUT_MAX_SIZE - ft_strlen(state->input));
	state->cursor--;
	return (NO_NEWLINE_FOUND);
}

static t_input_result	handle_delete_to_cursor(t_state *state)
{
	size_t	len;

	len = ft_strlen(state->input + state->cursor);
	ft_strcpy(state->input, state->input + state->cursor);
	ft_bzero(state->input + ft_strlen(state->input),
		INPUT_MAX_SIZE - state->cursor);
	state->cursor = 0;
	return (NO_NEWLINE_FOUND);
}

t_input_result	handle_key(char *buf, t_state *state)
{
	size_t								i;
	static const t_key_handler_dispatch	dispatch_table[] = {
	{RETURN_KEY, &handle_newline},
	{CTRL_W, &handle_delete_word},
	{BACKSPACE, &handle_delete_char},
	{TAB, &autocomplete},
	{CTRL_D, &ctrl_d},
	{CTRL_U, &handle_delete_to_cursor},
	{0, NULL}
	};

	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strnequ(dispatch_table[i].activator, buf,
				ft_strlen(dispatch_table[i].activator)))
			return (dispatch_table[i].run(state));
		i++;
	}
	return (NO_NEWLINE_FOUND);
}
