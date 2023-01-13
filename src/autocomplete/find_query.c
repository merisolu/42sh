/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_query.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:54:23 by amann             #+#    #+#             */
/*   Updated: 2023/01/13 15:19:42 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

char	*find_query(char *str, char c)
{
	size_t	len;
	size_t	start;

	len = ft_strlen(str);
	start = 0;
	while (len)
	{
		if (str[len] == c)
		{
			start = len + 1;
			break ;
		}
		len--;
	}
	return (ft_strdup(str + start));
}
