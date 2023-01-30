/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:49:38 by amann             #+#    #+#             */
/*   Updated: 2023/01/30 13:26:34 by amann            ###   ########.fr       */
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
	{'\0', TOKEN_NULL}
	};

	return (dispatch_table);
}

t_token_type	get_token_type(char value, t_tokenizer *t)
{
	bool in_quotes = t->in_quotes;
	bool in_braces = t->in_braces;
	bool backslash_inhibited = t->backslash_inhibited;
	const t_token_dispatch	*dispatch_table;
	size_t					i;

	if (in_quotes || in_braces || backslash_inhibited)
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
