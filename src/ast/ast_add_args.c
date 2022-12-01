/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:55:34 by amann             #+#    #+#             */
/*   Updated: 2022/12/01 14:50:39 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	realloc_array(char ***arr, size_t size)
{
	char	**res;
	size_t	i;

	res = (char **) ft_memalloc(sizeof(char *) * (size + 1));
	if (!res)
	{
		ft_free_null_array((void **) *arr);
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	}
	i = 0;
	while ((*arr)[i])
	{
		res[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = res;
	return (true);
}

static bool	check_cmd_end(t_token **cursor)
{
	t_token	*reset;

	reset = *cursor;
	if (eat_token(cursor, TOKEN_LT | TOKEN_GT, reset))
	{
		*cursor = reset;
		return (true);
	}
	if (ast_fd_agg_format_check(cursor))
		return (true);
	if (ast_is_separator(*cursor))
		return (true);
	if (!check_separator_syntax(*cursor))
		return (true);
	if ((*cursor)->type == TOKEN_PIPE && ft_strlen((*cursor)->value) == 1)
		return (true);
	return (false);
}

static size_t	set_size(size_t idx)
{
	size_t	ret;

	ret = idx;
	if (idx < 2)
		ret = 2;
	return (ret);
}

bool	allocate_args_array(char ***res, t_token **cursor)
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
					return (false);
			}
			(*res)[idx] = ft_strdup((*cursor)->value);
			if (!(*res)[idx])
				return (print_error_bool(false, ERR_MALLOC_FAIL));
			idx++;
		}
		else if ((*cursor)->type & (TOKEN_AMPERSAND | TOKEN_BACKSLASH))
			return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
		*cursor = (*cursor)->next;
	}
	return (true);
}
