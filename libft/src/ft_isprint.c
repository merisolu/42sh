/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:43:37 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/23 15:06:40 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns true if the given character is in the printable ascii range.
 * "Printable" means letters, digits, punctuation, etc. */
int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}
