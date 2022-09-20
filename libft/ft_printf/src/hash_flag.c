/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:43:01 by amann             #+#    #+#             */
/*   Updated: 2022/03/10 17:38:34 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*hex_hash_helper(char *res, t_conv conv, size_t len)
{
	char	*new;
	char	*lower_hex;
	char	*upper_hex;

	lower_hex = "0x";
	upper_hex = "0X";
	new = ft_strnew(len + 2);
	if (!new)
	{
		ft_memdel((void **)&res);
		return (NULL);
	}
	if (conv.x || conv.p)
		ft_strcpy(new, lower_hex);
	else
		ft_strcpy(new, upper_hex);
	ft_strcpy(new + 2, res);
	free(res);
	return (new);
}

/*	
*	Hexadecimal precision is handled in this part of the process, as the hash tag
*	results in 0 padding to happen between the conversion result an 0x prefix
*/

static char	*hex_precision(char *res, size_t prec)
{
	size_t	len;
	char	*new;

	if (!prec || !res)
		return (res);
	len = ft_strlen(res);
	if (len < prec)
	{
		new = ft_strnew(prec);
		if (!new)
		{
			free(res);
			return (NULL);
		}
		ft_memset(new, '0', prec - len);
		ft_strcpy(new + prec - len, res);
		free(res);
		return (new);
	}
	return (res);
}

char	*handle_hash(char *res, t_flags flag)
{
	char	*new;

	if (flag.conv.o)
	{
		new = ft_strnew(ft_strlen(res) + 1);
		if (!new)
		{
			free(res);
			return (NULL);
		}
		ft_memset(new, '0', 1);
		ft_strcpy(new + 1, res);
		free(res);
		return (new);
	}
	else if (flag.conv.x || flag.conv.big_x || flag.conv.p)
	{
		res = hex_precision(res, flag.width.prec);
		if (!res)
			return (NULL);
		if (flag.hash || flag.conv.p)
			return (hex_hash_helper(res, flag.conv, ft_strlen(res)));
	}
	return (res);
}
