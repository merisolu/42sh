/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:16:34 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/18 15:45:02 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
 * Parses the given status code returned by wait() and sets
 * the last_return_value of the given state accordingly.
 */
int	get_return_value_from_status(int status)
{
	if (WIFSTOPPED(status))
		return (RETURN_SUSPENDED);
	return (WEXITSTATUS(status));
}

/*
 * Sets the state's last_return_value to return_value.
 */

void	set_return_value(int return_value, t_state *state)
{
	state->last_return_value = return_value;
}
