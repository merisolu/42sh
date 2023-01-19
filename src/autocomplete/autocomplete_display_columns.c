/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_display_columns.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:20:19 by amann             #+#    #+#             */
/*   Updated: 2023/01/19 17:11:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static void	initialise_acd_struct(t_autocomplete_display *ad, \
		t_input_context ic, char ***search_result, size_t len)
{
	ad->max_len = find_longest(*search_result);
	ad->col_width = ad->max_len + 2;
	ad->total_cols = (ic.width / ad->col_width);
	if (ad->total_cols == 0)
		ad->total_cols = 1;
	else if (len % ad->total_cols)
		ad->total_cols -= 1;
	ad->col_height = (len / ad->total_cols);
	if (ad->col_height == 0)
		ad->col_height = 1;
	if (ad->total_cols < len && len % ad->total_cols > ad->total_cols / 2)
		ad->col_height += 1;
	ad->start_x = ic.input_start_x - 1;
	ad->start_y = ic.input_start_y - 1;
	ad->current_col = 0;
	ad->i = 0;
	ad->row_counter = 0;
	ad->offset = 0;
}

static void	display_loop(t_autocomplete_display *ad, char **search_result, \
		size_t len)
{
	size_t	count;

	count = 0;
	while (count < len)
	{
		ft_putstr(tgoto(tgetstr("cm", NULL),
				ad->start_x + (ad->current_col * ad->col_width),
				ad->start_y + ad->row_counter));
		ft_printf("%s", search_result[ad->i + ad->offset]);
		count++;
		(ad->current_col)++;
		ad->i += ad->col_height;
		if (ad->i + ad->offset >= len)
		{
			(ad->offset)++;
			ad->i = 0;
			(ad->row_counter)++;
			ad->current_col = 0;
			ft_putendl("");
		}
	}
	if (ad->current_col != 0)
		ft_putendl("");
}

void	autocomplete_display_columns(char **search_result, size_t len, \
		t_state *state)
{
	t_input_context			ic;
	t_autocomplete_display	ad;

	ic = state->input_context;
	ft_putendl("");
	save_cursor(&ic);
	initialise_acd_struct(&ad, ic, &search_result, len);
	display_loop(&ad, search_result, len);
	save_cursor(&(state->input_context));
}
