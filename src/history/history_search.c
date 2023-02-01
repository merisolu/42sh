/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:56:28 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/01 12:45:50 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static bool	research_called(t_input_result result, t_state *state)
{
	return (result == INPUT_FOUND_RESERVED_SEQUENCE
		&& ft_strequ(CTRL_R, state->input_context.found_reserved_sequence));
}

static char	*seek_in_history(t_state *state, size_t	*cursor, char *look_for,
							size_t *found_index)
{
	size_t	i;
	char	*temp;

	*found_index = 0;
	i = *cursor;
	while (i < HISTORY_SIZE)
	{
		temp = ft_strstr(state->history[i], look_for);
		if (temp)
		{
			*found_index = (size_t)(temp - state->history[i]);
			*cursor = i + 1;
			return (state->history[i]);
		}
		i++;
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

void	history_search(t_state *state)
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
		if (result == INPUT_NO_MARK_FOUND)
			seek_cursor = 0;
		search_result = seek_in_history(
				state, &seek_cursor, state->input_context.input, &found_index);
		print_search(&(state->input_context), search_result, found_index);
		if (result != INPUT_NO_MARK_FOUND && !research_called(result, state))
			break ;
	}
	if (search_result)
		ft_strcpy(state->input_context.input, search_result);
}
