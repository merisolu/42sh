/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir_recursion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:42:07 by amann             #+#    #+#             */
/*   Updated: 2022/11/17 19:13:59 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "debug.h"

bool	add_redir_struct(t_ast_redir ***redirs, t_ast_redir *new)
{
	size_t	len;

	if (!*redirs)
	{
		*redirs = (t_ast_redir **) ft_memalloc(sizeof(t_ast_redir *) * 2);
		if (!*redirs)
			return (print_bool_error(ERR_MALLOC_FAIL, false));
	}
	len = ft_null_array_len((void **)*redirs);
	if (len == 0)
	{
		(*redirs)[0] = new;
		return (true);
	}
	if (!ft_resize_null_array((void ***)redirs, len + 1))
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	(*redirs)[len] = new;
	return (true);
}


static bool	add_fd_agg(t_ast *node, t_token **cursor, t_token *reset)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	res->aggregation = true;
	if (read_token(cursor, TOKEN_GT | TOKEN_LT, reset))
	{
		if ((*cursor)->value[0] == '>')
			res->agg_from = STDOUT_FILENO;
		if ((*cursor)->value[0] == '<')
			res->agg_from = STDIN_FILENO;
	}
	else
	{
		res->agg_from = ft_atoi((*cursor)->value);
		eat_token(cursor, TOKEN_WORD, reset);
	}
	eat_token(cursor, TOKEN_GT | TOKEN_LT, reset);
	if ((*cursor)->value[0] == '-')
		res->agg_close = true;
	else
		res->agg_to = ft_atoi((*cursor)->value);
	eat_token(cursor, TOKEN_WORD, reset);
	return (add_redir_struct(&(node->redirs), res));
}

//TODO update ast_free

static bool	add_redir_in(t_ast *node, t_token **cursor)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	res->in_type = ft_strdup((*cursor)->value);
	if (!res->in_type)
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	*cursor = (*cursor)->next;
	res->in_file = ft_strdup((*cursor)->value);
	if (!res->in_file)
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	*cursor = (*cursor)->next;
	return (add_redir_struct(&(node->redirs), res));
}

static bool	add_redir_out(t_ast *node, t_token **cursor)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	res->out_type = ft_strdup((*cursor)->value);
	if (!res->out_type)
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	*cursor = (*cursor)->next;
	res->out_file = ft_strdup((*cursor)->value);
	if (!res->out_file)
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	*cursor = (*cursor)->next;
	return (add_redir_struct(&(node->redirs), res));
}

bool	ast_redirect_control(t_ast *node, t_token **cursor)
{
	t_token	*reset;

	reset = *cursor;
	if (ast_fd_agg_format_check(cursor) && !add_fd_agg(node, cursor, reset))
			return (false);
	reset = *cursor;
	if (*cursor	&& !ast_fd_agg_format_check(cursor)
		&& (!(*cursor)->next || (*cursor)->next->type != TOKEN_WORD))
		return (print_bool_syntax_error(ERR_SYNTAX, reset, false));
	if (!ast_fd_agg_format_check(cursor)
		&& eat_token(cursor, TOKEN_GT, reset)
		&& eat_token(cursor, TOKEN_WORD, reset)
		&& !add_redir_out(node, &reset))
		return (false);
	if (!ast_fd_agg_format_check(cursor)
		&& eat_token(cursor, TOKEN_LT, reset)
		&& eat_token(cursor, TOKEN_WORD, reset)
		&& !add_redir_in(node, &reset))
		return (false);
	return (true);
}
