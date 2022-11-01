/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:55:34 by amann             #+#    #+#             */
/*   Updated: 2022/11/01 16:01:33 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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
		return (print_error(ERR_MALLOC_FAIL, 0));
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
	t_token	*reset;

	reset = *cursor;
	if (read_token(cursor, TOKEN_SEMICOLON, reset)
		|| read_token(cursor, TOKEN_PIPE, reset)
		|| (read_token(cursor, TOKEN_LT, reset)
			&& !ft_strequ((*cursor)->value, FD_AGG_IN))
		|| (read_token(cursor, TOKEN_GT, reset)
			&& !ft_strequ((*cursor)->value, FD_AGG_OUT)))
		return (TRUE);
	if (ast_fd_agg_format_check(cursor))
		return (TRUE);
	return (FALSE);
}

static size_t	set_size(size_t idx)
{
	size_t	ret;

	ret = idx;
	if (idx < 2)
		ret = 2;
	return (ret);
}

int	allocate_args_array(char ***res, t_token **cursor)
{
	size_t	idx;
	size_t	size;

	idx = ft_null_array_len((void **) *res);
	size = set_size(idx);
	while (*cursor && !check_cmd_end(cursor))
	{
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
				return (print_error(ERR_MALLOC_FAIL, 0));
			idx++;
		}
		*cursor = (*cursor)->next;
	}
	return (1);
}
