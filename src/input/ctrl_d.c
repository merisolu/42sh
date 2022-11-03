/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:57:36 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/03 13:38:56 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ctrl_d(t_state *state)
{
	size_t	input_length;

	input_length = ft_strlen(state->input_context.input);
	if (input_length == 0)
	{
		state->exiting = 1;
		state->exit_return_value = RETURN_CTRL_D;
		return (-2);
	}
	if (state->input_context.cursor == input_length)
		ft_putstr(tgetstr("bl", NULL));
	else
	{
		ft_strcpy(state->input_context.input + state->input_context.cursor,
			state->input_context.input + state->input_context.cursor + 1);
		ft_bzero(state->input_context.input + input_length,
			INPUT_MAX_SIZE - input_length);
	}
	return (0);
}
