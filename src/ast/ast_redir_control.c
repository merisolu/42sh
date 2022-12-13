/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:42:07 by amann             #+#    #+#             */
/*   Updated: 2022/12/13 14:07:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	add_redir_in(t_ast *node, t_token **cursor)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!check_redir_syntax(*cursor))
	{
		free(res);
		return (false);
	}
	res->in_type = ft_strdup((*cursor)->value);
	if (!res->in_type)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	*cursor = (*cursor)->next;
	if ((*cursor)->type == TOKEN_WHITESPACE)
		*cursor = (*cursor)->next;
	res->in_file = ft_strdup((*cursor)->value);
	if (!res->in_file)
	{
		clear_redir_and_members(res);
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	}
	*cursor = (*cursor)->next;
	return (add_redir_struct(&(node->redirs), res));
}

static bool	add_redir_err(t_ast *node, t_token **cursor)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!check_redir_syntax(*cursor))
	{
		free(res);
		return (false);
	}
	res->err_type = ft_strdup((*cursor)->value);
	if (!res->err_type)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	*cursor = (*cursor)->next;
	if ((*cursor)->type == TOKEN_WHITESPACE)
		*cursor = (*cursor)->next;
	res->err_file = ft_strdup((*cursor)->value);
	if (!res->err_file)
	{
		clear_redir_and_members(res);
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	}
	*cursor = (*cursor)->next;
	return (add_redir_struct(&(node->redirs), res));
}

static bool	add_redir_out(t_ast *node, t_token **cursor)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	if (!check_redir_syntax(*cursor))
	{
		free(res);
		return (false);
	}
	res->out_type = ft_strdup((*cursor)->value);
	if (!res->out_type)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	*cursor = (*cursor)->next;
	if ((*cursor)->type == TOKEN_WHITESPACE)
		*cursor = (*cursor)->next;
	res->out_file = ft_strdup((*cursor)->value);
	if (!res->out_file)
	{
		clear_redir_and_members(res);
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	}
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
	if (!(*cursor) || (!((*cursor)->type & (TOKEN_LT | TOKEN_GT))
			&& !(((*cursor)->type == TOKEN_WORD && ft_isdigit_str((*cursor)->value)
			&& (*cursor)->next && (*cursor)->next->type & (TOKEN_LT | TOKEN_GT)))
			&& !ast_fd_agg_format_check(cursor)))
		return (true);
	while (*cursor)
	{
		if ((*cursor)->type == TOKEN_WORD && !ast_fd_agg_format_check(cursor))
		{
			if (ft_strequ((*cursor)->value, "2"))
			{
				*cursor = (*cursor)->next;
				if (!add_redir_err(node, cursor))
					return (false);
			}
			else if (ft_strequ((*cursor)->value, "1"))
			{
				*cursor = (*cursor)->next;
				if (!add_redir_out(node, cursor))
					return (false);
			}
			else if (ft_strequ((*cursor)->value, "0"))
			{
				*cursor = (*cursor)->next;
				if (!add_redir_in(node, cursor))
					return (false);
			}
			else
			{
				ft_putendl("bad filedes");
				return (false);
			}
		}
		else if (ast_fd_agg_format_check(cursor))
		{
			if (!ast_add_fd_agg(node, cursor))
				return (false);
		}
		else if ((*cursor)->type == TOKEN_GT)
		{
			if (!add_redir_out(node, cursor))
				return (false);
		}
		else if ((*cursor)->type == TOKEN_LT)
		{
			if (!add_redir_in(node, cursor))
				return (false);
		}
		else
			return (true);
	}
	return (true);
}
