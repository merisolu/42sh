/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:54:16 by amann             #+#    #+#             */
/*   Updated: 2022/12/16 16:11:53 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	check_redir_tokens(t_token **cursor)
{
	return ((*cursor)->type & (TOKEN_LT | TOKEN_GT)
		|| ((*cursor)->type == TOKEN_WORD && ft_isdigit_str((*cursor)->value)
			&& (*cursor)->next
			&& (*cursor)->next->type & (TOKEN_LT | TOKEN_GT)));
}
