/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_fd_agg_format_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:54:25 by amann             #+#    #+#             */
/*   Updated: 2022/11/18 15:51:47 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	ft_isdigit_str(char *s)
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

static bool	format_helper(t_token **cursor)
{
	if (ft_isdigit_str((*cursor)->value)
		&& (ft_strequ((*cursor)->next->value, FD_AGG_IN)
			|| ft_strequ((*cursor)->next->value, FD_AGG_OUT))
		&& (ft_isdigit_str((*cursor)->next->next->value)
			|| ft_strequ((*cursor)->next->next->value, "-")))
		return (true);
	return (false);
}

static bool	format_helper_part_two(t_token **cursor)
{
	if ((*cursor)->next
		&& (ft_isdigit_str((*cursor)->next->value)
		|| ft_strequ((*cursor)->next->value, "-")))
		return (true);
	return (false);
}

bool	ast_fd_agg_format_check(t_token **cursor)
{
	t_token	*reset;

	if (!cursor || !*cursor)
		return (false);
	reset = *cursor;
	if (eat_token(cursor, TOKEN_WORD, reset)
		&& eat_token(cursor, TOKEN_GT | TOKEN_LT, reset)
		&& eat_token(cursor, TOKEN_WORD, reset))
	{
		*cursor = reset;
		if (format_helper(cursor))
			return (true);
	}
	if (read_token(cursor, TOKEN_GT | TOKEN_LT, reset)
		&& (ft_strequ((*cursor)->value, FD_AGG_OUT)
			|| (ft_strequ((*cursor)->value, FD_AGG_IN))))
	{
		*cursor = reset;
		if (format_helper_part_two(cursor))
			return (true);
	}
	return (false);
}
