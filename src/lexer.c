/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/09/28 15:31:29 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_token_type	get_token_type(char value)
{
	if (ft_is_whitespace(value))
		return (TOKEN_WHITESPACE);
	if (value == '$')
		return (TOKEN_DOLLAR);
	if (value == '~')
		return (TOKEN_TILDE);
	if (value == '"')
		return (TOKEN_DOUBLEQUOTE);
	if (value == '{')
		return (TOKEN_CURLY_OPEN);
	if (value == '}')
		return (TOKEN_CURLY_CLOSED);
	if (value == '+')
		return (TOKEN_PLUS);
	if (value == '-')
		return (TOKEN_MINUS);
	return (TOKEN_LITERAL);
}

t_token	*tokenize(char *line)
{
	t_token			*result;
	t_token_type	type;
	int				changed;
	int				i;

	result = NULL;
	i = 0;
	while (line[i] && get_token_type(line[i]) == TOKEN_WHITESPACE)
		i++;
	changed = i;
	type = get_token_type(line[i]);
	while (line[i])
	{
		if ((get_token_type(line[i]) != type
				|| (type != TOKEN_LITERAL && type != TOKEN_WHITESPACE))
			&& (i - changed) > 0)
		{
			token_add(&result, type, ft_strsub(line, changed, i - changed));
			type = get_token_type(line[i]);
			changed = i;
		}
		i++;
	}
	token_add(&result, type, ft_strsub(line, changed, i - changed));
	return (result);
}
