/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:51:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/08 13:41:29 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	input_context_set(t_input_context *context, char *start_prompt, \
char *multiline_prompt, char *mark)
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
	context->start_prompt = start_prompt;
	context->multiline_prompt = multiline_prompt;
	context->mark = mark;
	return (1);
}

void	input_context_free(t_input_context *context)
{
	free(context->input);
	free(context->clipboard);
}
