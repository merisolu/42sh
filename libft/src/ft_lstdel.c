/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:00:32 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:07:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Deletes all the elements in the list alst, using function ft_lstdelone.
 * Sets the pointer to the list to NULL at the end. */
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*cursor;
	t_list	*next;

	cursor = *alst;
	while (cursor)
	{
		next = cursor->next;
		ft_lstdelone(&cursor, del);
		cursor = next;
	}
	*alst = NULL;
}
