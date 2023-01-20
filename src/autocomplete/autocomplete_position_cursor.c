/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_position_cursor.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:43:26 by amann             #+#    #+#             */
/*   Updated: 2023/01/20 13:45:50 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

void	cursor_to_end(t_input_context *ic, size_t *orig_cursor)
{
	*orig_cursor = ic->cursor;
	ic->cursor = ft_strlen(ic->input);
	move_cursor_to_saved_position(ic);
	ft_putchar('\n');
	save_cursor(ic);
}

void	cursor_to_orig(t_input_context *ic, size_t orig_cursor)
{
	save_cursor(ic);
	ic->cursor = orig_cursor;
	move_cursor_to_saved_position(ic);
}
