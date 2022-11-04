/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendequ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:43:16 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/04 15:35:34 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Checks the end of s1 and returns 1 if it matches s2. Returns 0 otherwise.
 */
int	ft_strendequ(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len < s2_len)
		return (0);
	return (ft_strequ((s1 + s1_len) - s2_len, s2));
}
