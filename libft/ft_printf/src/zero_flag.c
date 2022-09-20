/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:23:42 by amann             #+#    #+#             */
/*   Updated: 2022/03/10 16:44:53 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hash_zero_hex(char *new, char x)
{
	int	i;

	i = 0;
	while (new[i] != '\0')
	{
		if (new[i] == x)
		{
			new[i] = '0';
			break ;
		}
		i++;
	}
	new[1] = x;
}

static char	*handle_zero_neg(char *res, int len)
{
	char	*temp;

	temp = ft_strnew(len);
	if (!temp)
	{
		free(res);
		return (NULL);
	}
	ft_strcpy(temp, res + 1);
	free(res);
	return (temp);
}

static void	handle_zero_helper(char *new, t_flags flag)
{
	if (flag.conv.big_x && flag.hash)
		hash_zero_hex(new, 'X');
	if (flag.conv.x && flag.hash)
		hash_zero_hex(new, 'x');
	if (flag.conv.neg && (flag.conv.d || flag.conv.f))
		new[0] = '-';
}

static int	zero_neg_checker(t_flags flag, int len)
{
	if (flag.conv.neg)
	{
		if (flag.conv.d || flag.conv.f)
		{
			if (flag.width.width > len)
				return (TRUE);
		}
	}
	return (FALSE);
}

char	*handle_zero(char *res, t_flags flag)
{
	char	*new;
	int		len;

	len = (int) ft_strlen(res);
	if (zero_neg_checker(flag, len))
		res = handle_zero_neg(res, --len);
	if (!res)
		return (NULL);
	if (len > flag.width.width)
		return (res);
	new = ft_strnew(flag.width.width + 1);
	if (!new)
	{
		ft_memdel((void **)&res);
		return (NULL);
	}
	ft_memset(new, '0', flag.width.width - len);
	ft_strcpy(new + flag.width.width - len, res);
	free(res);
	handle_zero_helper(new, flag);
	return (new);
}
