/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:56:28 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/31 15:12:05 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static char	*seek_in_history(t_state *state, char *look_for)
{
	size_t	i;

	i = 0;
	while (i < HISTORY_SIZE)
	{
		if (ft_strstr(state->history[i], look_for))
			return (state->history[i]);
		i++;
	}
	return (NULL);
}

static void	print_search(char *query, char *search_result)
{
	ft_printf("%s%s(reverse-i-search)`%s': %s",
		tgetstr("cr", NULL), tgetstr("cd", NULL), query, search_result);
}

void	history_search(t_state *state)
{
	t_input_result	result;
	char			*search_result;

	search_result = NULL;
	ft_strclr(state->input_context.input);
	print_search(state->input_context.input, search_result);
	state->input_context.cursor = 0;
	while (1)
	{
		result = get_input(&(state->input_context));
		if (result == INPUT_NOTHING_READ)
			continue ;
		search_result = seek_in_history(state, state->input_context.input);
		move_cursor_to_saved_position(&(state->input_context));
		print_search(state->input_context.input, search_result);
		if (result != INPUT_NO_MARK_FOUND)
			break ;
	}
	if (search_result)
		ft_strcpy(state->input_context.input, search_result);
}
