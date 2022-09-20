/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:15:49 by jumanner          #+#    #+#             */
/*   Updated: 2021/11/15 11:16:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns true if the given character c is considered whitespace. */
int	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\f' || c == '\r' || \
	c == '\t' || c == '\v');
}
