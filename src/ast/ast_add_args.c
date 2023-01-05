/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:55:34 by amann             #+#    #+#             */
/*   Updated: 2023/01/05 15:20:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	check_cmd_end(t_token **cursor)
{
	if (((*cursor)->type == TOKEN_WORD && ft_isdigit_str((*cursor)->value)
			&& (*cursor)->next && (*cursor)->next->type & (TOKEN_LT | TOKEN_GT))
		|| ((*cursor)->type & (TOKEN_LT | TOKEN_GT)
			|| ast_fd_agg_format_check(cursor) || ast_is_separator(*cursor)
			|| !check_separator_syntax(*cursor, false)
			|| ((*cursor)->type == TOKEN_PIPE
				&& ft_strlen((*cursor)->value) == 1)))
		return (true);
	return (false);
}

static bool	check_intern(t_ast **node, t_token **cursor)
{
	size_t	idx;

	if (ft_null_array_len((void **)(*node)->arg_list))
		return (true);
	if ((*cursor)->type == TOKEN_WHITESPACE)
		*cursor = (*cursor)->next;
	idx = 0;
	while (*cursor && check_var_syntax((*cursor)->value))
	{
		((*node)->var_list)[idx] = ft_strdup((*cursor)->value);
		if (!(((*node)->var_list)[idx]))
			return (print_error_bool(false, ERR_MALLOC_FAIL));
		idx++;
		*cursor = (*cursor)->next;
		if (*cursor && (*cursor)->type == TOKEN_WHITESPACE)
			*cursor = (*cursor)->next;
	}
	return (true);
}

bool	allocate_args_array(t_ast **node, t_token **cursor)
{
	size_t	idx;

	if (!check_intern(node, cursor))
		return (false);
	idx = ft_null_array_len((void **)(*node)->arg_list);
	while (*cursor && !check_cmd_end(cursor))
	{
		if ((*cursor)->type == TOKEN_WORD)
		{
			((*node)->arg_list)[idx] = ft_strdup((*cursor)->value);
			if (!((*node)->arg_list)[idx])
				return (print_error_bool(false,
						ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
			idx++;
		}
		else if ((*cursor)->type == TOKEN_AMPERSAND)
			return (print_bool_sep_error(ERR_SYNTAX, *cursor, false));
		*cursor = (*cursor)->next;
	}
	return (true);
}
