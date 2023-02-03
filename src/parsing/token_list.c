/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:11:09 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 14:26:17 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	token_list_free(t_token **list)
{
	t_token	*cursor;
	t_token	*temp;

	cursor = *list;
	while (cursor)
	{
		temp = cursor->next;
		token_free(&cursor);
		cursor = temp;
	}
	*list = NULL;
}
