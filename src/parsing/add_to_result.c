/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_result.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:11:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/14 15:02:08 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	continue_word(char **res, char *value)
{
	char	*temp;

	ft_strdel(res);
	temp = ft_strjoin(*res, value);
	if (!temp)
		return (-1);
	*res = ft_strdup(temp);
	free(temp);
	if (!(*res))
		return (-1);
	return (1);
}

int	add_to_result(char **res, char *value, t_state *state)
{
	if (!value)
		return (-1);
	if (state->continue_previous_node)
		return (continue_word(res, value));
	else
	{
		state->continue_previous_node = 1;
		ft_strdel(res);
		*res = ft_strdup(value);
		if (!(*res))
			return (-1);
		return (1);
	}
	return (-1);
}
