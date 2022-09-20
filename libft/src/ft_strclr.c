/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:41:56 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/10 11:51:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Uses ft_memset to set all characters in the string to \0 */
void	ft_strclr(char *s)
{
	if (!s)
		return ;
	ft_memset(s, '\0', ft_strlen(s));
}
