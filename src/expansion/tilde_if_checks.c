/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_if_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:43:29 by amann             #+#    #+#             */
/*   Updated: 2023/02/02 17:44:08 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	basic_exp(t_token **csr, t_token *fb, t_state *s, t_token_type scn)
{
	if ((eat_token(csr, TOKEN_TILDE, fb) && read_token(csr, scn, fb))
		|| (eat_token(csr, TOKEN_TILDE, fb)
			&& check_recursive(csr, s, fb, TOKEN_CURLY_CLOSED | scn)))
		return (true);
	return (false);
}

bool	minus_exp(t_token **csr, t_token *fb, t_state *s, t_token_type scn)
{
	if ((eat_token(csr, TOKEN_TILDE, fb) && eat_token(csr, TOKEN_MINUS, fb)
		&& read_token(csr, scn, fb)) || (eat_token(csr, TOKEN_TILDE, fb)
			&& eat_token(csr, TOKEN_MINUS, fb)
			&& check_recursive(csr, s, fb, TOKEN_CURLY_CLOSED | scn)))
		return (true);
	return (false);
}

bool	plus_exp(t_token **csr, t_token *fb, t_state *s, t_token_type scn)
{
	if ((eat_token(csr, TOKEN_TILDE, fb) && eat_token(csr, TOKEN_PLUS, fb)
		&& read_token(csr, scn, fb)) || (eat_token(csr, TOKEN_TILDE, fb)
			&& eat_token(csr, TOKEN_PLUS, fb)
			&& check_recursive(csr, s, fb, TOKEN_CURLY_CLOSED | scn)))
		return (true);
	return (false);
}
