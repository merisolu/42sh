/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:56:28 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/02 13:43:29 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static bool	should_exit(t_input_result result, t_state *state)
{
	return (result == INPUT_MARK_FOUND || result == INPUT_CALLED_FOR_EXIT
		|| (result == INPUT_FOUND_RESERVED_SEQUENCE
			&& !ft_strequ(CTRL_R,
				state->input_context.found_reserved_sequence)));
}

static char	*seek_in_history(t_state *state, size_t	*cursor, char *look_for,
							size_t *found_index)
{
	size_t	i;
	size_t	found;
	char	*temp;

	*found_index = 0;
	i = *cursor;
	found = history_seek(state, *cursor, look_for, true);
	temp = ft_strstr(state->history[found], look_for);
	if (temp)
	{
		*found_index = (size_t)(temp - state->history[found]);
		*cursor = found + 1;
		return (state->history[found]);
	}
	if (*cursor == 0)
		return (NULL);
	return (state->history[*cursor - 1]);
}

static void	print_search(t_input_context *ctx, char *search_result,
						size_t found_index)
{
	size_t	prompt_length;
	size_t	total_length;
	size_t	rows;

	ctx->cursor = ft_strlen(ctx->input);
	load_cursor(ctx);
	ft_printf("%s%s(reverse-i-search)`%s': %s",
		tgetstr("cr", NULL), tgetstr("cd", NULL), ctx->input, search_result);
	prompt_length = ft_strlen("(reverse-i-search)") + ft_strlen(ctx->input) + 4;
	total_length = prompt_length + ft_strlen(search_result) - 1;
	rows = ft_min_size_t((total_length / ctx->width), ctx->height);
	if (ctx->input_start_y + rows >= ctx->height)
		ctx->input_start_y -= (ctx->input_start_y + rows) - ctx->height;
	ft_putstr(tgoto(tgetstr("ch", NULL),
			0, (prompt_length + found_index) % ctx->width));
}

bool	history_search(t_state *state)
{
	t_input_result	result;
	char			*search_result;
	size_t			seek_cursor;
	size_t			found_index;

	seek_cursor = 0;
	search_result = NULL;
	clear_input(&(state->input_context));
	print_search(&(state->input_context), search_result, 0);
	while (1)
	{
		result = get_input(&(state->input_context));
		if (result == INPUT_NOTHING_READ)
			continue ;
		if (should_exit(result, state))
			break ;
		if (result == INPUT_NO_MARK_FOUND)
			seek_cursor = 0;
		search_result = seek_in_history(
				state, &seek_cursor, state->input_context.input, &found_index);
		print_search(&(state->input_context), search_result, found_index);
	}
	ft_strcpy(state->input_context.input, search_result);
	state->input_context.cursor = ft_strlen(state->input_context.input);
	return (result == INPUT_MARK_FOUND);
}
