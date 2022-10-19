/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:55:34 by amann             #+#    #+#             */
/*   Updated: 2022/10/19 13:32:10 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * NB: the below process will result in trailing NULL pointers in our args
 * array, maybe this should be tidied up...
 */

static int	realloc_array(char ***arr, size_t size)
{
	char	**res;
	size_t	i;

	res = (char **) ft_memalloc(sizeof(char *) * (size + 1));
	if (!res)
	{
		ft_free_null_array((void **) *arr);
		return (0);
	}
	i = 0;
	while ((*arr)[i])
	{
		res[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = res;
	return (1);
}

static int	check_cmd_end(t_token **cursor)
{
	if ((*cursor)->type == TOKEN_SEMICOLON || (*cursor)->type == TOKEN_PIPE
		|| (*cursor)->type == TOKEN_LT || (*cursor)->type == TOKEN_GT)
		return (1);
	return (0);
}

static int	allocate_args_array(char ***res, t_token **cursor)
{
	size_t	idx;
	size_t	size;

	size = 2;
	idx = 0;
	while (*cursor)
	{
		if (check_cmd_end(cursor))
			return (1);
		if ((*cursor)->type == TOKEN_WORD)
		{
			if (idx >= size)
			{
				size *= 2;
				if (!realloc_array(res, size))
					return (0);
			}
			(*res)[idx] = ft_strdup((*cursor)->value);
			if (!(*res)[idx])
				return (0);
			idx++;
		}
		*cursor = (*cursor)->next;
	}
	return (1);
}

char	**ast_add_args(t_token **cursor)
{
	char	**res;

	res = (char **) ft_memalloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	if (!(allocate_args_array(&res, cursor)))
	{
		ft_free_null_array((void **)res);
		return (NULL);
	}
	return (res);
}
