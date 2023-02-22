/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_handle_dot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:27:48 by amann             #+#    #+#             */
/*   Updated: 2023/02/22 17:29:34 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

int	autocomplete_handle_dot(t_state *state, char *ti)
{
	free(ti);
	if (state->input_context.cursor + 1 >= INPUT_MAX_SIZE
		|| ft_strlen(state->input_context.input) + 1 >= INPUT_MAX_SIZE)
		return (1);
	ft_memmove(
		state->input_context.input + state->input_context.cursor + 1,
		state->input_context.input + state->input_context.cursor,
		ft_strlen(state->input_context.input + state->input_context.cursor)
		);
	state->input_context.input[state->input_context.cursor] = '/';
	(state->input_context.cursor)++;
	return (1);
}
