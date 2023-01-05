/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:22:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/27 12:14:24 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

int	cleanup(t_state *state, int return_value)
{
	if (state->terminal_conf_applied
		&& !terminal_apply_config(&(state->orig_conf)))
		return (print_error(1, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	if (*state->history)
		ft_free_array_elements((void **)state->history, HISTORY_SIZE);
	ft_free_null_array((void **)(state->env));
	hash_table_clear(state->hash_table);
	free(state->hash_table);
	input_context_free(&(state->input_context));
	return (return_value);
}
