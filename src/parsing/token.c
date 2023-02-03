/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:54:56 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 14:30:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token	*token_new(t_token_type type, char *value, t_token *previous)
{
	t_token	*result;

	result = (t_token *)malloc(sizeof(t_token));
	if (!result)
	{
		free(value);
		return (NULL);
	}
	result->value = value;
	result->type = type;
	result->next = NULL;
	result->previous = previous;
	return (result);
}

t_token	*token_add(t_token **list, t_token_type type, char *value)
{
	t_token	*cursor;

	if (!list)
	{
		free(value);
		return (NULL);
	}
	if (!(*list))
	{
		*list = token_new(type, value, NULL);
		return (*list);
	}
	cursor = *list;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = token_new(type, value, cursor);
	return (cursor->next);
}

void	token_free(t_token **token)
{
	if (!token || !(*token))
		return ;
	ft_memdel((void **)&((*token)->value));
	ft_memdel((void **) token);
}
