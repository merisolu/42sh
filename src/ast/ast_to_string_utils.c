/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:51:25 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/26 11:07:17 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

char	*ast_string_builder(char *s1, char *s2)
{
	char	*temp;

	if (s1[0] != '\0')
		temp = ft_strjoinfree(s1, " ");
	else
		temp = s1;
	return (ft_strjoinfree(temp, s2));
}

char	*ast_string_builder_int(char *s1, int i)
{
	char	*temp;
	char	*number;

	temp = ft_strjoinfree(s1, " ");
	if (!temp)
		return (NULL);
	number = ft_itoa(i);
	if (!number)
	{
		free(s1);
		return (NULL);
	}
	temp = ft_strjoinfree(temp, number);
	free(number);
	return (temp);
}
