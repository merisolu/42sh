/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env_intern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:49:42 by amann             #+#    #+#             */
/*   Updated: 2023/01/16 17:11:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static size_t	find_equals(char *str)
{
	size_t	res;

	res = 0;
	while (str[res])
	{
		if (str[res] == '=')
			return (res);
		res++;
	}
	return (0);
}

static bool	free_temp_return(char *temp)
{
	free(temp);
	return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
			ERR_MALLOC_FAIL));
}

static bool	allocate_new_result(char ***sr, size_t *count, char *temp, bool b)
{
	if (b)
	{
		(*(sr))[*count] = ft_strnew(sizeof(char) * (ft_strlen(temp) + 3));
		if (!((*(sr))[*count]))
			return (free_temp_return(temp));
		(*(sr))[*count][0] = '$';
		(*(sr))[*count][1] = '{';
		ft_strcpy(((*(sr))[*count]) + 2, temp);
		(*(sr))[*count][ft_strlen(temp) + 2] = '}';
	}
	else
	{
		(*(sr))[*count] = ft_strnew(sizeof(char) * (ft_strlen(temp) + 1));
		if (!((*(sr))[*count]))
			return (free_temp_return(temp));
		(*(sr))[*count][0] = '$';
		ft_strcpy(((*(sr))[*count]) + 1, temp);
	}
	free(temp);
	(*count)++;
	return (true);
}

static char	*get_temp(char *const *arr, size_t i)
{
	size_t	equals_idx;
	char	*res;

	equals_idx = find_equals(arr[i]);
	if (equals_idx == 0)
		return (NULL);
	res = ft_strndup(arr[i], equals_idx);
	if (!res)
		return ((char *)print_error_ptr(NULL, ERRTEMPLATE_SIMPLE,
				ERR_MALLOC_FAIL));
	return (res);
}

bool	search_env_intern(char *const *arr, char *query, char ***sr, bool b)
{
	size_t	i;
	size_t	count;
	size_t	len;
	char	*temp;

	len = ft_strlen(query);
	count = ft_null_array_len((void **)*sr);
	i = 0;
	while (arr[i])
	{
		if (ft_strnequ(arr[i], query, len))
		{
			temp = get_temp(arr, i);
			if (!temp)
				return (false);
			if (!allocate_new_result(sr, &count, temp, b))
				return (false);
		}
		if (count >= INPUT_MAX_SIZE - 1)
			return (true);
		i++;
	}
	return (true);
}
