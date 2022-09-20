/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:53:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/01/18 13:35:26 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Writes the given character n times to the given file descriptor. */
void	ft_putcharn(char c, int n)
{
	ft_putcharn_fd(c, n, 1);
}
