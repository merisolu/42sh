/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:42:07 by amann             #+#    #+#             */
/*   Updated: 2022/12/20 15:16:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	set_specified_fd(t_ast_redir **res, t_token **cursor)
{
	(*res)->redir_fd = ft_atoi((*cursor)->value);
	if ((*res)->redir_fd > 9)
	{
		ft_memdel((void **)res);
		return (print_error_bool(false, ERR_BAD_FD));
	}
	*cursor = (*cursor)->next;
	return (true);
}

static bool	set_redir_op(t_ast_redir **res, t_token **cursor)
{
	(*res)->redir_op = ft_strdup((*cursor)->value);
	if (!(*res)->redir_op)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	(*res)->redir_out = false;
	if (ft_strequ((*res)->redir_op, REDIR_OUT)
		|| ft_strequ((*res)->redir_op, FD_AGG_OUT)
		|| ft_strequ((*res)->redir_op, REDIR_APPEND))
		(*res)->redir_out = true;
	*cursor = (*cursor)->next;
	return (true);
}

static bool	set_redir_file(t_ast_redir **res, t_token **cursor)
{
	(*res)->redir_file = ft_strdup((*cursor)->value);
	if (!(*res)->redir_file)
	{
		clear_redir_and_members(*res);
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	}
	return (true);
}

static bool	add_redir(t_ast *node, t_token **cursor)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	res->redir_fd = -1;
	if ((*cursor)->type == TOKEN_WORD && !set_specified_fd(&res, cursor))
		return (false);
	if (!check_redir_syntax(*cursor))
	{
		free(res);
		return (false);
	}
	if (!set_redir_op(&res, cursor))
		return (false);
	if ((*cursor)->type == TOKEN_WHITESPACE)
		*cursor = (*cursor)->next;
	if (!set_redir_file(&res, cursor))
		return (false);
	*cursor = (*cursor)->next;
	return (add_redir_struct(&(node->redirs), res));
}

/*
 * First, we must filter out separators or null, as we will call this function
 * if these are detected in ast_add_args.
 *
 * We then loop through the tokens, checking for fd aggregation or redirects,
 * and handling them accordingly, until we hit a sequence of tokens not matching
 * the syntax.
 *
 * Bad syntax, for example no file to redirect into or ">>>>>",  will be managed
 * by the respective handler functions; to keep this loop as clean and minimal
 * as possible.
 */

bool	ast_redirect_control(t_ast *node, t_token **cursor)
{
	if (!(*cursor) || (!check_redir_tokens(cursor)
			&& !ast_fd_agg_format_check(cursor)))
		return (true);
	while (*cursor)
	{
		if (ast_fd_agg_format_check(cursor))
		{
			if (!ast_add_fd_agg(node, cursor))
				return (false);
		}
		else if (check_redir_tokens(cursor))
		{
			if (!add_redir(node, cursor))
				return (false);
		}
		else
			return (true);
	}
	return (true);
}
