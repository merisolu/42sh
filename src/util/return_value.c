/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:16:34 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 13:06:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

/*
 * Parses the given status code returned by wait() and sets
 * the last_return_value of the given state accordingly.
 */
int	get_return_value_from_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

/*
 * Sets the state's last_return_value to return_value.
 */
void	set_return_value(int return_value, t_state *state)
{
	state->last_return_value = return_value;
}
