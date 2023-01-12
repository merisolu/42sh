/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:37:40 by amann             #+#    #+#             */
/*   Updated: 2023/01/12 18:52:08 by amann            ###   ########.fr       */
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

static bool	search_env_intern(char *const *arr, char *query, char ***sr, bool brackets)
{
	size_t	i;
	size_t	count;
	size_t	len;
	size_t	equals_idx;

	char *temp;

	len = ft_strlen(query);
	count = ft_null_array_len((void **)*sr);
	i = 0;
	while (arr[i])
	{
		if (ft_strnequ(arr[i], query, len))
		{
			equals_idx = find_equals(arr[i]);
			if (equals_idx == 0)
				return (false);
			temp = ft_strndup(arr[i], equals_idx);
			if (!temp)
				return (false);

			if (brackets)
			{
				(*(sr))[count] = ft_strnew(sizeof(char) * (ft_strlen(temp) + 3));
				if (!((*(sr))[count]))
					return (false);
				(*(sr))[count][0] = '$';
				(*(sr))[count][1] = '{';
				ft_strcpy(((*(sr))[count]) + 2, temp);
				(*(sr))[count][ft_strlen(temp) + 2] = '}';
			}
			else
			{
				(*(sr))[count] = ft_strnew(sizeof(char) * (ft_strlen(temp) + 1));
				if (!((*(sr))[count]))
					return (false);
				(*(sr))[count][0] = '$';
				ft_strcpy(((*(sr))[count]) + 1, temp);
			}
			free(temp);
			count++;
		}
		i++;
	}
	return (true);
}

char	**search_variables(t_state *state, char **ti, bool second_tab)
{
	char	**search_result;
	char	*dollar_start;
	char	*query;
	bool	brackets;

	(void) second_tab;
	search_result = (char **) ft_memalloc(sizeof(char *) * INPUT_MAX_SIZE);
	if (!search_result)
		return (print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	dollar_start = ft_strchr(*ti, '$');
	brackets = *(dollar_start + 1) == '{';
	query = dollar_start + 1;
	if (brackets)
		query = dollar_start + 2;
	if (!search_env_intern(state->env, query, &search_result, brackets)
		|| !search_env_intern(state->intern, query, &search_result, brackets))
	{
		ft_free_null_array((void **)search_result);
		return (NULL);
	}
	return (search_result);
}
