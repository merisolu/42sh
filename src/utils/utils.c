/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/03 13:05:47 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*var_copy(void *var)
{
	return ((void *)ft_strdup((const char *)var));
}

void	clear_input(t_input_context *context, int newline)
{
	ft_bzero(context->input, INPUT_MAX_SIZE);
	context->cursor = 0;
	if (newline)
		ft_putchar('\n');
}

void	update_window_size(t_input_context *context)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == -1)
		return ;
	context->width = size.ws_col;
	context->height = size.ws_row;
}
