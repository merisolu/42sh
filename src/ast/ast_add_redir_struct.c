/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_redir_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:55:08 by amann             #+#    #+#             */
/*   Updated: 2023/02/13 13:24:37 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	clear_print_error(t_ast_redir *new)
{
	clear_redir_and_members(new);
	return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
}

bool	add_redir_struct(t_ast_redir ***redirs, t_ast_redir *new)
{
	size_t	len;

	if (!*redirs)
	{
		*redirs = (t_ast_redir **) ft_memalloc(sizeof(t_ast_redir *) * 2);
		if (!*redirs)
			return (clear_print_error(new));
	}
	len = ft_null_array_len((void **)*redirs);
	if (len == 0)
	{
		(*redirs)[0] = new;
		return (true);
	}
	if (!ft_resize_null_array((void ***)redirs, len + 1))
		return (clear_print_error(new));
	(*redirs)[len] = new;
	return (true);
}
