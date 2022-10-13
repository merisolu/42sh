/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/13 13:46:08 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_token_dispatch	*get_token_dispatch(void)
{
	static const t_token_dispatch	dispatch_table[] = {
	{'$', TOKEN_DOLLAR},
	{'~', TOKEN_TILDE},
	{'"', TOKEN_DOUBLE_QUOTE},
	{'\'', TOKEN_SINGLE_QUOTE},
	{'{', TOKEN_CURLY_OPEN},
	{'}', TOKEN_CURLY_CLOSED},
//	{'+', TOKEN_PLUS},
//	{'-', TOKEN_MINUS},
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

static t_token_type	get_token_type(char value)
{
	const t_token_dispatch	*dispatch_table;
	size_t					i;

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
				|| (type != TOKEN_WORD && type != TOKEN_WHITESPACE))
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
