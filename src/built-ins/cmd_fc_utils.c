/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:24:41 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/22 10:37:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

bool	cmd_fc_check_empty_history_errors(t_state *state, char *flags)
{
	if (ft_strlen(state->history[1]) != 0)
		return (false);
	if (!ft_strchr(flags, 'l'))
		clear_input(&(state->input_context));
	return (print_error_bool(true, ERRTEMPLATE_NAMED,
			"fc", ERR_HISTORY_SPEC_OUT_OF_RANGE));
}
