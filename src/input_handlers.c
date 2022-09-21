/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:29:22 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/21 11:55:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_newline(char buf[BUF_SIZE], t_state *state)
{
	(void)buf;
	state->cursor = ft_strlen(PROMPT);
	return (1);
}

static int	handle_delete_word(char buf[BUF_SIZE], t_state *state)
{
	char	*temp;
	size_t	del_count;

	(void)buf;
	if (!(ft_strlen(state->input) > 0 && state->cursor > ft_strlen(PROMPT)))
		return (0);
	temp = ft_strdelword(
			state->input, state->cursor - ft_strlen(PROMPT) - 1, &del_count
			);
	if (!temp)
		return (-1);
	free(state->input);
	state->input = temp;
	state->cursor -= del_count;
	return (0);
}

static int	handle_delete_char(char buf[BUF_SIZE], t_state *state)
{
	char	*temp;

	(void)buf;
	if (!(ft_strlen(state->input) > 0 && state->cursor > ft_strlen(PROMPT)))
		return (0);
	temp = ft_strdelchar(state->input, state->cursor - ft_strlen(PROMPT) - 1);
	if (!temp)
		return (-1);
	free(state->input);
	state->input = temp;
	state->cursor--;
	return (0);
}

int	handle_char(char buf[BUF_SIZE], int *index, t_state *state)
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
	if (ft_isprint(buf[*index]))
		state->cursor++;
	return (0);
}
