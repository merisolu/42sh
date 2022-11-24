/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_is_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:27:19 by amann             #+#    #+#             */
/*   Updated: 2022/11/24 17:15:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	ast_is_separator(t_token *token)
{
	if (!token)
		return (false);
	if (token->type == TOKEN_SEMICOLON)
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
