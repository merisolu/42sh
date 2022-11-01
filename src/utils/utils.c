/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 15:04:16 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*var_copy(void *var)
{
	return ((void *)ft_strdup((const char *)var));
}

void	clear_input(t_state *state, int newline)
{
	ft_bzero(state->input, INPUT_MAX_SIZE);
	state->cursor = 0;
	if (newline)
		ft_putchar('\n');
}

void	update_window_size(t_state *state)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == -1)
		return ;
	state->width = size.ws_col;
	state->height = size.ws_row;
}
