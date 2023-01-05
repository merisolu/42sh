/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:34:06 by amann             #+#    #+#             */
/*   Updated: 2023/01/05 14:43:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

bool	setup_input(t_state *state)
{
	if (state->input_context.width == 0 || state->input_context.height == 0)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
				ERR_WINDOW_TOO_SMALL));
	if (!terminal_get_configs(&(state->input_conf), &(state->orig_conf)))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	if (!terminal_apply_config(&(state->input_conf)))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	state->terminal_conf_applied = true;
	return (true);
}
