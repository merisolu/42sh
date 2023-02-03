/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_param_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:04:44 by amann             #+#    #+#             */
/*   Updated: 2023/02/02 17:30:25 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	check_recursive(t_token **csr, t_state *s, t_token *fb, \
		t_token_type token_type)
{
	if (s->in_braces && read_token(csr, token_type, fb))
		return (true);
	*csr = fb;
	return (false);
}

bool	check_param_exp(t_state *s, t_token *fb)
{
	if (s->in_braces && fb->previous->type & (TOKEN_PLUS | TOKEN_MINUS \
		| TOKEN_QUESTION_MARK | TOKEN_HASH | TOKEN_PERCENT | TOKEN_EQUALS))
		return (true);
	return (false);
}
