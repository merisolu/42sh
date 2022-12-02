/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_fd_agg_format_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:54:25 by amann             #+#    #+#             */
/*   Updated: 2022/12/02 16:07:36 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"


#include "debug.h"

bool	ft_isdigit_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ast_fd_agg_format_check(t_token **cursor)
{
	if (!cursor || !*cursor)
		return (false);
	if ((*cursor)->type & (TOKEN_LT | TOKEN_GT))
	{
		if ((ft_strequ((*cursor)->value, FD_AGG_IN)
				|| ft_strequ((*cursor)->value, FD_AGG_OUT))
			&& (ft_isdigit_str((*cursor)->next->value)
				|| ft_strequ((*cursor)->next->value, "-")))
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
