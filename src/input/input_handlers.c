/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:29:22 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/10 11:45:34 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_input_result	handle_newline(t_state *state)
{
	if (state->input[ft_strlen(state->input) - 1] != '\\')
	{
		state->cursor = 0;
		return (INPUT_NEWLINE_FOUND);
	}
	return (INPUT_NO_NEWLINE_FOUND);
}

static t_input_result	handle_delete_char(t_state *state)
{
	if (state->cursor == 0)
		return (INPUT_NO_NEWLINE_FOUND);
	ft_strcpy(state->input + state->cursor - 1, state->input + state->cursor);
	ft_bzero(state->input + ft_strlen(state->input),
		INPUT_MAX_SIZE - ft_strlen(state->input));
	state->cursor--;
	return (INPUT_NO_NEWLINE_FOUND);
}

t_input_result	handle_key(char *buf, t_state *state)
{
	size_t								i;
	static const t_key_handler_dispatch	dispatch_table[] = {
	{RETURN_KEY, &handle_newline},
	{BACKSPACE, &handle_delete_char},
	{TAB, &autocomplete},
	{CTRL_D, &ctrl_d},
	{CTRL_K, &cut_from_cursor},
	{CTRL_U, &cut_to_cursor},
	{CTRL_W, &cut_word},
	{CTRL_Y, &paste},
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
	return (INPUT_NO_NEWLINE_FOUND);
}
