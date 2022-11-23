/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_logical_ops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:58:45 by amann             #+#    #+#             */
/*   Updated: 2022/11/23 15:59:14 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_logical_ops(t_ast **ast, t_state *state, int *i)
{
	if ((ast[*i]->and_or == TOKEN_AMPERSAND && state->last_return_value == 0)
		|| (ast[*i]->and_or == TOKEN_PIPE && state->last_return_value != 0))
		(*i)++;
	else if (ast[*i]->and_or == TOKEN_AMPERSAND && state->last_return_value != 0)
	{
		while (ast[*i] && ast[*i]->and_or == TOKEN_AMPERSAND)
			(*i)++;
		if (ast[*i])
			(*i)++;
	}
	else if (ast[*i]->and_or == TOKEN_PIPE && state->last_return_value == 0)
	{
		while (ast[*i] && ast[*i]->and_or == TOKEN_PIPE)
			(*i)++;
		if (ast[*i])
			(*i)++;
	}
	else
		(*i)++;
}

