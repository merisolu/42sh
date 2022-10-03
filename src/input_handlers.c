/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:29:22 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/03 16:05:47 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_newline(char buf[BUF_SIZE], t_state *state)
{
	(void)buf;
	state->cursor = 0;
	return (1);
}

static int	handle_delete_word(char buf[BUF_SIZE], t_state *state)
{
	size_t	len;
	size_t	end;
	size_t	start;

	(void)buf;
	if (!(ft_strlen(state->input) > 0 && state->cursor > 0))
		return (0);
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
	state->cursor -= end - start + 1;
	return (0);
}

static int	handle_delete_char(char buf[BUF_SIZE], t_state *state)
{
	(void)buf;
	if (state->cursor == 0)
		return (0);
	ft_strcpy(state->input + state->cursor - 1, state->input + state->cursor);
	state->cursor--;
	return (0);
}

int	handle_char(char buf[BUF_SIZE], t_state *state)
{
	size_t									i;
	static const t_input_handler_dispatch	dispatch_table[] = {
	{RETURN_KEY, &handle_newline},
	{CTRL_W, &handle_delete_word},
	{BACKSPACE, &handle_delete_char},
	{0, NULL}
	};

	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strequ(dispatch_table[i].activator, buf))
			return (dispatch_table[i].run(buf, state));
		i++;
	}
	return (0);
}
