/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_fd_agg_format_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:54:25 by amann             #+#    #+#             */
/*   Updated: 2023/01/19 11:02:18 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	ast_fd_agg_format_check(t_token **cursor)
{
	if (!cursor || !*cursor)
		return (false);
	if ((*cursor)->type & (TOKEN_LT | TOKEN_GT))
	{
		if ((ft_strequ((*cursor)->value, FD_AGG_IN)
				|| ft_strequ((*cursor)->value, FD_AGG_OUT))
			&& ((*cursor)->next && (ft_isdigit_str((*cursor)->next->value)
					|| ft_strequ((*cursor)->next->value, "-"))))
			return (true);
		return (false);
	}
	if ((*cursor)->type == TOKEN_WORD)
	{
		if (!ft_isdigit_str((*cursor)->value))
			return (false);
		if (!((*cursor)->next) || !((*cursor)->next->next))
			return (false);
		if ((ft_strequ((*cursor)->next->value, FD_AGG_IN)
				|| ft_strequ((*cursor)->next->value, FD_AGG_OUT))
			&& (*cursor)->next->next->type == TOKEN_WORD)
			return (true);
		return (false);
	}
	return (false);
}
