/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:55:34 by amann             #+#    #+#             */
/*   Updated: 2022/10/27 15:40:26 by amann            ###   ########.fr       */
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

int	ft_isdigit_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ast_fd_agg_format_check(t_token **cursor)
{
	t_token	*reset;

	reset = *cursor;
	if (eat_token(cursor, TOKEN_WORD, reset)
		&& eat_token(cursor, TOKEN_GT | TOKEN_LT, reset)
		&& eat_token(cursor, TOKEN_WORD , reset))
	{
		*cursor = reset;
		if (ft_isdigit_str((*cursor)->value)
			&& (ft_strequ((*cursor)->next->value, FD_AGG_IN)
				|| ft_strequ((*cursor)->next->value, FD_AGG_OUT))
			&& (ft_isdigit_str((*cursor)->next->next->value)
				|| ft_strequ((*cursor)->next->next->value, "-")))
			return (TRUE);
	}
	if (read_token(cursor, TOKEN_GT | TOKEN_LT, reset)
		&& (ft_strequ((*cursor)->value, FD_AGG_OUT)
			|| (ft_strequ((*cursor)->value, FD_AGG_IN))))
	{
		if (eat_token(cursor, TOKEN_GT | TOKEN_LT, reset)
			&& (ft_isdigit_str((*cursor)->value)
				|| ft_strequ((*cursor)->value, "-")))
		{
			*cursor = reset;
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	check_cmd_end(t_token **cursor)
{
	t_token	*reset;

	reset = *cursor;
	if (read_token(cursor, TOKEN_SEMICOLON, reset) || read_token(cursor, TOKEN_PIPE, reset)
		|| (read_token(cursor, TOKEN_LT, reset) && !ft_strequ((*cursor)->value, FD_AGG_IN))
		|| (read_token(cursor, TOKEN_GT, reset) && !ft_strequ((*cursor)->value, FD_AGG_OUT)))
		return (TRUE);
	if (ast_fd_agg_format_check(cursor))
		return (TRUE);
	return (FALSE);
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
				return (print_error(ERR_MALLOC_FAIL, 0));
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
	{
		print_error(ERR_MALLOC_FAIL, 0);
		return (NULL);
	}
	if (!(allocate_args_array(&res, cursor)))
	{
		ft_free_null_array((void **)res);
		return (NULL);
	}
	return (res);
}
