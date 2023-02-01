/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:10:58 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/01 14:29:08 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

/* 
 * Applies history expansions to the input context in *state. Returns 0 if no
 * expansions were applied, 1 if they were, and -1 on malloc error.
 */
int	history_expand(t_state *state)
{
	char	*temp;

	if (!ft_strstr(state->input_context.input, "!!"))
		return (0);
	temp = ft_strreplace(state->input_context.input, "!!", state->history[1]);
	if (!temp)
		return (-1);
	ft_strncpy(state->input_context.input, temp, INPUT_MAX_SIZE);
	free(temp);
	return (1);
}
