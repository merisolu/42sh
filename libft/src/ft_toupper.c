/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:38:09 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/08 12:42:34 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Converts lowercase letters to uppercase letters.
 * 32 is the offset between lower- and uppercase letters on the ascii table.*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
