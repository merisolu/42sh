/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:57:36 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/05 14:11:17 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ctrl_d(t_state *state)
{
	if (ft_strlen(state->input) == 0)
	{
		state->exiting = 1;
		state->exit_return_value = RETURN_CTRL_D;
		return (-2);
	}
	if (state->cursor == ft_strlen(state->input))
	{
		ft_putstr(tgetstr("bl", NULL));
		ft_putstr(tgetstr("vb", NULL));
	}
	else
	{
		ft_strcpy(state->input + state->cursor,
			state->input + state->cursor + 1);
		ft_bzero(state->input + ft_strlen(state->input),
			INPUT_MAX_SIZE - ft_strlen(state->input));
	}
	return (0);
}
