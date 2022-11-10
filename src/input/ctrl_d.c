/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:57:36 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/10 11:39:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ctrl_d(t_input_context *context)
{
	size_t	input_length;

	input_length = ft_strlen(context->input);
	if (input_length == 0 || context->input[input_length - 1] == '\n')
		return (-1);
	if (context->cursor == input_length)
		ft_putstr(tgetstr("bl", NULL));
	else
	{
		ft_strcpy(context->input + context->cursor,
			context->input + context->cursor + 1);
		ft_bzero(context->input + input_length,
			INPUT_MAX_SIZE - input_length);
	}
	return (0);
}
