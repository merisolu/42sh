/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_fd_aggregation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:24:05 by amann             #+#    #+#             */
/*   Updated: 2022/12/02 14:35:25 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int	set_fd(char c)
{
	if (c == '>')
		return (STDOUT_FILENO);
	return (STDIN_FILENO);
}

static bool	ambiguous_redir(t_ast_redir **res, char *val)
{
	ft_memdel((void **)res);
	return (print_error_bool(
			false, ETEMPLATE_SHELL_NAMED, val, ERR_AMBIGUOUS_REDIR));
}

bool	ast_add_fd_agg(t_ast *node, t_token **cursor)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_error_bool(false, ERR_MALLOC_FAIL));
	res->aggregation = true;
	if ((*cursor)->type & (TOKEN_GT | TOKEN_LT))
		res->agg_from = set_fd((*cursor)->value[0]);
	else
	{
		res->agg_from = ft_atoi((*cursor)->value);
		*cursor = (*cursor)->next;
	}
	*cursor = (*cursor)->next;
	if ((*cursor)->value[0] == '-')
		res->agg_close = true;
	else if (!ft_isdigit_str((*cursor)->value) && res->agg_from != 1)
		return (ambiguous_redir(&res, (*cursor)->value));
	else
		res->agg_to = ft_atoi((*cursor)->value);
	*cursor = (*cursor)->next;
	return (add_redir_struct(&(node->redirs), res));
}
