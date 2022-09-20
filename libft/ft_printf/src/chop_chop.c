/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chop_chop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:45:56 by amann             #+#    #+#             */
/*   Updated: 2022/03/11 18:13:43 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*chop_chop_helper(char **res_str, size_t t, size_t len)
{
	char	*new;

	new = ft_strnew(t);
	if (!new)
		return (NULL);
	ft_strcpy(new, *res_str);
	ft_memset((void *)(new + len), '0', t - len);
	return (new);
}

void	chop_chop(char **res_str, size_t prec, unsigned int hash)
{
	size_t	i;
	size_t	total;
	size_t	len;
	char	*new;

	len = ft_strlen(*res_str);
	i = 0;
	while ((*res_str)[i] != '.')
		i++;
	total = prec + i + 1;
	if (prec == 0)
	{
		if (hash)
			new = ft_strndup(*res_str, i + 1);
		else
			new = ft_strndup(*res_str, i);
	}
	else if (total < len)
		new = ft_strndup(*res_str, total);
	else
		new = chop_chop_helper(res_str, total, len);
	if (!new)
		return ;
	free(*res_str);
	*res_str = new;
}
