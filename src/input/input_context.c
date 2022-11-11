/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:51:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/10 15:46:54 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	input_context_set(t_input_context *context, t_input_initializer *init)
{
	ft_bzero(context, sizeof(t_input_context));
	context->input = ft_strnew(INPUT_MAX_SIZE);
	if (!context->input)
		return (0);
	context->clipboard = ft_strnew(INPUT_MAX_SIZE);
	if (!context->clipboard)
		return (0);
	context->max_length = INPUT_MAX_SIZE;
	update_window_size(context);
	context->start_prompt = init->start_prompt;
	context->multiline_prompt = init->multiline_prompt;
	context->mark = init->mark;
	context->reserved_sequences = init->reserved_sequences;
	return (1);
}

void	input_context_free(t_input_context *context)
{
	free(context->input);
	free(context->clipboard);
}
