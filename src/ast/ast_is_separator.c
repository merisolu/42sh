/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:27:19 by amann             #+#    #+#             */
/*   Updated: 2022/12/19 16:55:49 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	ast_is_separator(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TOKEN_SEMICOLON && ft_strlen(token->value) == 1)
		return (true);
	if ((token->type == TOKEN_AMPERSAND || token->type == TOKEN_PIPE)
		&& (ft_strlen(token->value) == 2))
		return (true);
	return (false);
}

int	ast_is_logic_op(t_token **cursor)
{
	int	ret;

	if (!*cursor)
		return (0);
	if (((*cursor)->type == TOKEN_AMPERSAND || (*cursor)->type == TOKEN_PIPE)
		&& (ft_strlen((*cursor)->value) == 2))
	{
		ret = (*cursor)->type;
		return (ret);
	}
	return (0);
}

static t_token	*set_token_len(t_token *cursor)
{
	if (cursor->type == TOKEN_SEMICOLON)
	{
		if (ft_strlen(cursor->value) > 1)
			(cursor->value)[2] = '\0';
		else
			(cursor->value)[1] = '\0';
	}
	else if (ft_strlen(cursor->value) > 2)
		(cursor->value)[2] = '\0';
	else
		(cursor->value)[1] = '\0';
	return (cursor);
}

bool	check_separator_syntax(t_token *cursor, bool print)
{
	if (cursor->type == TOKEN_SEMICOLON && ft_strlen(cursor->value) != 1)
	{
		if (print)
			return (print_bool_sep_error(ERR_SYNTAX, set_token_len(cursor),
					false));
		return (false);
	}
	if (cursor->type == TOKEN_PIPE && ft_strlen(cursor->value) != 2)
	{
		if (print)
			return (print_bool_sep_error(ERR_SYNTAX, set_token_len(cursor),
					false));
		return (false);
	}
	if (cursor->type == TOKEN_AMPERSAND && ft_strlen(cursor->value) > 2)
	{
		if (print)
			return (print_bool_sep_error(ERR_SYNTAX, set_token_len(cursor),
					false));
		return (false);
	}
	return (true);
}
