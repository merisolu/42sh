/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2023/10/10 16:10:20 by amann            ###   ########.fr       */
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

void	print_tokens(t_token *list)
{
	while (list)
	{
		ft_printf("type: %d | value: %s\n", list->type, list->value);
		list = list->next;
	}
}
