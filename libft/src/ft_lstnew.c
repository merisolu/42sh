/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:21:57 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:07:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Creates a new element in a list and returns it. */
t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*result;

	result = (t_list *)malloc(sizeof(t_list));
	if (!result)
		return (NULL);
	if (content)
	{
		result->content = (void *)malloc(content_size);
		if (!result->content)
		{
			free(result);
			return (NULL);
		}
		ft_memcpy(result->content, content, content_size);
	}
	else
	{
		result->content = NULL;
		content_size = 0;
	}
	result->content_size = content_size;
	result->next = NULL;
	return (result);
}
