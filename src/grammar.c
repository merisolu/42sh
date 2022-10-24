/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:27:35 by amann             #+#    #+#             */
/*   Updated: 2022/10/21 18:26:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	sc_count(t_token *list)
{
	size_t	res;

	res = 1;
	while (list)
	{
		if (list->type == TOKEN_SEMICOLON)
			res++;
		list = list->next;
	}
	return (res);
}

/*
 * In order to manage the semicolons effectively, we construct a separate tree
 * for each complete command, then pass that array of trees back to the parser
 *
 * The root node of each tree will be a pipe_sequence, with only one node if
 * nothing is being piped.
 */

t_ast	**construct_ast_list(t_token **cursor)
{
	t_token	*reset;
	t_ast	**tree_list;
	size_t	idx;
	size_t	len;

	reset = *cursor;
	len = sc_count(*cursor);
	tree_list = (t_ast **) ft_memalloc(sizeof(t_ast *) * (len + 1));
	if (!tree_list)
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		tree_list[idx] = ast_pipe_sequence(cursor);
		if (!tree_list[idx])
		{
			ast_free(tree_list);
			return (NULL);
		}
		idx++;
		if (*cursor)
			*cursor = (*cursor)->next;
	}
	return (tree_list);
}
