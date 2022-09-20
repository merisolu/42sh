/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:47:33 by amann             #+#    #+#             */
/*   Updated: 2022/03/30 14:37:29 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*neg_float_handler(char *res, t_flags *flag)
{
	char	*neg_res;

	if (flag->conv.neg)
	{
		neg_res = ft_strjoin("-", res);
		free(res);
		return (neg_res);
	}
	return (res);
}

static char	a_h2(char **res, size_t *len)
{
	size_t	i;

	i = 1;
	while ((*res)[*len + i] != '\0')
	{
		if ((*res)[*len + i] != '0')
			break ;
		i++;
	}
	return ((*res)[*len + i]);
}

static void	algo_helper(char **r, size_t *l)
{
	size_t	c;

	while (*l)
	{
		c = 1;
		if ((*r)[*l] == '.')
			(*l)--;
		else
		{
			if ((*r)[*l - c] == '.')
				c = 2;
			if ((*r)[*l - c] == '9')
			{
				(*r)[*l - c] = '0';
				(*l)--;
			}
			else
			{
				if ((*r)[*l] == '5' && !a_h2(r, l) && ((*r)[*l - c] + 1) % 2)
					break ;
				(*r)[*l - c] += 1;
				break ;
			}
		}
	}
}

static size_t	set_len(char *res, size_t prec)
{
	size_t	len;
	size_t	res_len;

	len = 0;
	while (res[len] != '.')
		len++;
	len += prec + 1;
	res_len = ft_strlen(res);
	if (len > res_len)
		len = res_len;
	return (len);
}

char	*rounding_algo(char *res, size_t prec)
{
	size_t	len;
	char	*new;

	len = set_len(res, prec);
	if (res[len] < '5')
	{
		new = ft_strndup(res, len);
		free(res);
		return (new);
	}
	if (res[len] >= '5')
		algo_helper(&res, &len);
	if (len == 0 && (res)[len] == '0')
	{
		new = ft_strjoin("1", res);
		free(res);
		return (new);
	}
	return (res);
}
