/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:05:46 by amann             #+#    #+#             */
/*   Updated: 2022/03/10 17:42:47 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*width_helper(char *res, int len, t_width width, t_flags flag)
{
	char	*new;

	new = ft_strnew(width.width);
	if (!new)
		return (NULL);
	if (!flag.left)
	{
		ft_memset((void *)new, ' ', (size_t)(width.width - len));
		ft_strcpy((new + (width.width - len)), res);
	}
	else
	{
		ft_strcpy(new, res);
		ft_memset((void *)(new + len), ' ', (size_t)(width.width - len));
	}
	return (new);
}

static void	precision_helper_part_2(char *res, char *n, t_width w, int len)
{
	if (w.prec > len && w.prec > w.width)
	{
		ft_memset((void *)n, '0', (size_t)(w.prec - len));
		ft_strcpy((n + (w.prec - len)), res);
	}
	else if (w.prec > len && w.width)
	{
		ft_memset((void *)n, ' ', (size_t) w.width);
		ft_memset((void *)(n + w.width - w.prec), '0', (size_t)(w.prec - len));
		ft_strcpy((n + (w.width - len)), res);
	}
}

void	precision_helper(char *res, char *new, t_width w, t_flags flag)
{
	int	len;

	len = (int) ft_strlen(res);
	if (flag.conv.neg && w.prec > (len - 1))
		w.prec += 1;
	precision_helper_part_2(res, new, w, len);
	if (w.prec > len && w.width && flag.left)
	{
		ft_memset((void *)new, '0', (size_t)(w.prec - len));
		ft_strcpy(new + w.prec - len, res);
		if (w.prec < w.width)
			ft_memset((void *)(new + w.prec), ' ', (size_t)(w.width - w.prec));
	}
	if (flag.conv.neg && w.prec > (len - 1))
	{
		res = ft_strchr(new, '0');
		res[0] = '-';
	}
}

char	*set_memory(char *res, t_width w, t_flags flag)
{
	char	*new;
	int		len;

	len = (int) ft_strlen(res);
	if (flag.conv.neg && w.prec > (len - 1))
	{
		res[0] = '0';
		w.prec += 1;
	}
	if (w.prec && w.prec > len && w.width < w.prec && flag.conv.numeric)
		new = ft_strnew(w.prec);
	else if (w.width && w.width > len)
		new = width_helper(res, len, w, flag);
	else
		new = ft_strdup(res);
	return (new);
}
