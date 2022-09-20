/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:58:44 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/08 12:41:45 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns true if the given int is within the ascii range. */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
