/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:19:12 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/08 12:42:25 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Converts uppercase letters to lowercase letters.
 * 32 is the offset between upper- and lowercase letters on the ascii table. */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
