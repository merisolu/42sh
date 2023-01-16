/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_display_columns.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:20:19 by amann             #+#    #+#             */
/*   Updated: 2023/01/16 20:16:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static void	initialise_acd_struct(t_autocomplete_display *ad, \
		t_input_context ic, char **search_result, size_t len)
{
	ad->max_len = find_longest(search_result);
	ad->col_width = ad->max_len + 2;
	ad->total_cols = ic.width / ad->col_width;
	if (ad->total_cols == 0)
		ad->total_cols = 1;
	ad->col_height = (len / ad->total_cols) + 1;
	if (len * ad->col_width < ic.width)
		ad->col_height = 1;
	ad->start_x = ic.input_start_x - 1;
	ad->start_y = ic.input_start_y;
	if (len > 100)
		ad->start_y += 1;
	ad->current_col = 0;
	ad->i = 0;
	ad->row_counter = 0;
	ad->offset = 0;
}

static void	display_loop(t_autocomplete_display *ad, char **search_result, \
		t_input_context ic)
{
	while (search_result[ad->i])
	{
		if (ad->row_counter >= ad->col_height)
		{
			ad->row_counter = 0;
			if (ad->current_col == 0 && ad->offset)
				ad->start_y -= ad->offset + 2;
			ad->current_col++;
		}
		ft_putstr(tgoto(tgetstr("cm", NULL),
				ad->start_x + (ad->current_col * ad->col_width),
				ad->start_y + ad->row_counter));
		ft_printf("%s", search_result[ad->i]);
		if (ad->col_height > 1)
			ft_putendl("");
		if (ad->start_y + ad->row_counter > ic.height)
			(ad->offset)++;
		(ad->i)++;
		(ad->row_counter)++;
	}
}

void	autocomplete_display_columns(char **search_result, size_t len, \
		t_state *state)
{
	t_input_context			ic;
	t_autocomplete_display	ad;

	ic = state->input_context;
	ft_putendl("");
	save_cursor(&ic);
	initialise_acd_struct(&ad, ic, search_result, len);
	display_loop(&ad, search_result, ic);
	if (ad.start_y + ad.col_height > ic.height)
		ft_putendl("");
	ft_putstr(tgoto(tgetstr("cm", NULL),
			ad.start_x,
			ad.start_y + ad.col_height));
	save_cursor(&(state->input_context));
}
