/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:36:03 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/08 11:16:37 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Uses ft_memdel to free the memory allocated to the string pointed to by as
 * and then sets its pointer to null. */
void	ft_strdel(char **as)
{
	ft_memdel((void **)as);
}
