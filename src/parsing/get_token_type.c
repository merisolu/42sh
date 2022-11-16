/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:49:38 by amann             #+#    #+#             */
/*   Updated: 2022/11/16 17:49:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static const t_token_dispatch	*get_token_dispatch(void)
{
	static const t_token_dispatch	dispatch_table[] = {
	{'|', TOKEN_PIPE},
	{';', TOKEN_SEMICOLON},
	{'>', TOKEN_GT},
	{'<', TOKEN_LT},
	{'&', TOKEN_AMPERSAND},
	{'\\', TOKEN_BACKSLASH},
	{'\0', TOKEN_NULL}
	};

	return (dispatch_table);
}

t_token_type	get_token_type(char value, bool in_quotes)
{
	const t_token_dispatch	*dispatch_table;
	size_t					i;

	if (in_quotes)
		return (TOKEN_WORD);
	dispatch_table = get_token_dispatch();
	i = 0;
	while (dispatch_table[i].token != TOKEN_NULL)
	{
		if (dispatch_table[i].symbol == value)
			return (dispatch_table[i].token);
		i++;
	}
	if (ft_is_whitespace(value))
		return (TOKEN_WHITESPACE);
	return (TOKEN_WORD);
}
