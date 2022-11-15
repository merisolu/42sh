/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:27:35 by amann             #+#    #+#             */
/*   Updated: 2022/11/15 18:10:43 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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

static void	tree_list_loop(t_ast ***tree_list, t_token **cursor, size_t len)
{
	size_t	idx;
	int		ret;

	idx = 0;
	while (idx < len)
	{
		ret = ast_pipe_sequence(cursor, &((*tree_list)[idx]));
		if (!ret)
		{
			ast_free(tree_list);
			return ;
		}
		if (!*cursor)
			return ;
		idx++;
	}
}

t_ast	**construct_ast_list(t_token *cursor)
{
	t_ast	**tree_list;
	size_t	len;
	t_token	*reset;

	if (!cursor)
		return (NULL);
	ast_cleanse_ws(&cursor);
	reset = cursor;
	len = sc_count(cursor);
	tree_list = (t_ast **) ft_memalloc(sizeof(t_ast *) * (len + 1));
	if (!tree_list)
		return (NULL);
	tree_list_loop(&tree_list, &cursor, len);
	cursor = reset;
	token_list_free(&cursor);
	return (tree_list);
}
