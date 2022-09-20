/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:54:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/01/18 12:10:13 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Writes the given string up to n chars or until the null-byte to the
 * standard output.
*/
void	ft_putstrn(char const *s, const int n)
{
	ft_putstrn_fd(s, n, 1);
}
