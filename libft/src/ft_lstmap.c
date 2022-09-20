/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:59:26 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:07:38 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Recursively creates a new list by applying the function f to the list lst.
 * Returns the newly created list. */
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;

	if (!lst || !f)
		return (NULL);
	result = f(lst);
	if (!result)
		return (NULL);
	if (lst->next)
	{
		result->next = ft_lstmap(lst->next, f);
		if (!result->next)
		{
			free(result);
			return (NULL);
		}
	}
	else
		result->next = NULL;
	return (result);
}
