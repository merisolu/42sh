/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:56:28 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/31 15:33:05 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static bool	research_called(t_input_result result, t_state *state)
{
	return (result == INPUT_FOUND_RESERVED_SEQUENCE
		&& ft_strequ(CTRL_R, state->input_context.found_reserved_sequence));
}

static char	*seek_in_history(t_state *state, size_t	*cursor, char *look_for)
{
	size_t	i;

	i = *cursor;
	while (i < HISTORY_SIZE)
	{
		if (ft_strstr(state->history[i], look_for))
		{
			*cursor = i + 1;
			return (state->history[i]);
		}
		i++;
	}
	if (*cursor == 0)
		return (NULL);
	return (state->history[*cursor - 1]);
}

static void	print_search(t_input_context *ctx, char *search_result)
{
	move_cursor_to_saved_position(ctx);
	ft_printf("%s%s(reverse-i-search)`%s': %s",
		tgetstr("cr", NULL), tgetstr("cd", NULL), ctx->input, search_result);
}

void	history_search(t_state *state)
{
	t_input_result	result;
	char			*search_result;
	size_t			seek_cursor;

	seek_cursor = 0;
	search_result = NULL;
	clear_input(&(state->input_context));
	print_search(&(state->input_context), search_result);
	while (1)
	{
		result = get_input(&(state->input_context));
		if (result == INPUT_NOTHING_READ)
			continue ;
		if (result == INPUT_NO_MARK_FOUND)
			seek_cursor = 0;
		search_result = seek_in_history(
				state, &seek_cursor, state->input_context.input);
		print_search(&(state->input_context), search_result);
		if (result != INPUT_NO_MARK_FOUND && !research_called(result, state))
			break ;
	}
	if (search_result)
		ft_strcpy(state->input_context.input, search_result);
}
