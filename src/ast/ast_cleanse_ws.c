/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cleanse_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:39:45 by amann             #+#    #+#             */
/*   Updated: 2022/10/27 11:35:04 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	set_pointers(t_token **cursor, t_token **temp)
{
	if ((*cursor)->previous == NULL)
		*temp = (*cursor)->next;
	else if ((*cursor)->next == NULL)
	{
		*temp = NULL;
		(*cursor)->previous->next = NULL;
	}
	else
	{
		(*cursor)->previous->next = (*cursor)->next;
		(*cursor)->next->previous = (*cursor)->previous;
		*temp = (*cursor)->next;
	}
}

void	ast_cleanse_ws(t_token **list)
{
	t_token	*cursor;
	t_token	*temp;

	cursor = *list;
	temp = NULL;
	while (cursor)
	{
		if (cursor->type == TOKEN_WHITESPACE)
		{
			set_pointers(&cursor, &temp);
			free(cursor->value);
			free(cursor);
			cursor = temp;
		}
		else
			cursor = cursor->next;
	}
}
