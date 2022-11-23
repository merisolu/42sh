/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_logical_ops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:58:45 by amann             #+#    #+#             */
/*   Updated: 2022/11/23 16:56:22 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_logical_ops(t_ast **ast, t_state *s, int *i)
{
//	t_ast *node

//	node = ast[*i];
//	while (node->left && node->left->node_type == AST_PIPE_SEQUENCE)
//		node = node->left;

//	ft_printf("%d %d\n", s->last_return_value, ast[*i]->and_or);
	if ((ast[*i]->and_or == TOKEN_AMPERSAND && s->last_return_value == 0)
		|| (ast[*i]->and_or == TOKEN_PIPE && s->last_return_value != 0))
		(*i)++;
	else if (ast[*i]->and_or == TOKEN_AMPERSAND && s->last_return_value != 0)
	{
		while (ast[*i] && ast[*i]->and_or == TOKEN_AMPERSAND)
			(*i)++;
		if (ast[*i])
			(*i)++;
	}
	else if (ast[*i]->and_or == TOKEN_PIPE && s->last_return_value == 0)
	{
//		ft_putendl("here");
		while (ast[*i] && ast[*i]->and_or == TOKEN_PIPE)
			(*i)++;
		if (ast[*i])
			(*i)++;
	}
	else
		(*i)++;
}
