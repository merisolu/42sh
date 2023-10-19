/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2023/10/19 12:01:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*var_copy(void *var)
{
	return ((void *)ft_strdup((const char *)var));
}

void	clear_input(t_input_context *context)
{
	ft_bzero(context->input, INPUT_MAX_SIZE);
	context->cursor = 0;
}

void	update_window_size(t_input_context *context)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == -1)
		return ;
	context->width = size.ws_col;
	context->height = size.ws_row;
}

static size_t	get_token_type_max_width(t_token *list)
{
	float	max;
	size_t	current_value;
	size_t	res;

	max = 0;
	while (list)
	{
		current_value = list->type;
		if (current_value > max)
			max = current_value;
		list = list->next;
	}
	res = 1;
	while (max > 1)
	{
		max = max / 10;
		res += 1;
	}
	return res;
}

void	print_tokens(t_token *list)
{
	size_t width;

	width = get_token_type_max_width(list);
	while (list)
	{
		ft_printf("type: %*d | value: %s\n", width, list->type, list->value);
		list = list->next;
	}
}
