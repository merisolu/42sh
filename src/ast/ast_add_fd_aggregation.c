/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_fd_aggregation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:24:05 by amann             #+#    #+#             */
/*   Updated: 2022/11/21 14:40:19 by amann            ###   ########.fr       */
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
	return (print_bool_named_error(val, ERR_AMBIGUOUS_REDIR, false));
}

bool	ast_add_fd_agg(t_ast *node, t_token **cursor, t_token *reset)
{
	t_ast_redir	*res;

	res = (t_ast_redir *) ft_memalloc(sizeof(t_ast_redir));
	if (!res)
		return (print_bool_error(ERR_MALLOC_FAIL, false));
	res->aggregation = true;
	if (read_token(cursor, TOKEN_GT | TOKEN_LT, reset))
		res->agg_from = set_fd((*cursor)->value[0]);
	else
	{
		res->agg_from = ft_atoi((*cursor)->value);
		eat_token(cursor, TOKEN_WORD, reset);
	}
	eat_token(cursor, TOKEN_GT | TOKEN_LT, reset);
	if ((*cursor)->value[0] == '-')
		res->agg_close = true;
	else if (!ft_isdigit_str((*cursor)->value))
		return (ambiguous_redir(&res, (*cursor)->value));
	else
		res->agg_to = ft_atoi((*cursor)->value);
	eat_token(cursor, TOKEN_WORD, reset);
	return (add_redir_struct(&(node->redirs), res));
}
