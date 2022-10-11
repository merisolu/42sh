/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:23:36 by amann             #+#    #+#             */
/*   Updated: 2022/10/11 16:14:01 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	token_semicolon_count(t_token *list)
{
	size_t res;

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
int	separator(t_token **cursor, t_token *reset)
{
	if ((*cursor)->type == TOKEN_SEMICOLON || (*cursor)->type == TOKEN_NEWLINE)
	{
		*cursor = (*cursor)->next;
		return (TRUE);
	}
	*cursor = reset;
	return (FALSE);
}*/

int	cmd_name(t_token **cursor, t_token *reset)
{
	(void) reset;
	if ((*cursor)->type == TOKEN_WORD)
		return (TRUE);
	return (FALSE);
}

t_ast	*simple_command(t_token **cursor, t_token *reset)
{
	t_ast	*res;

	res = NULL;
	if (cmd_name(cursor, reset))
	{
		res = (t_ast *) malloc(sizeof(t_ast));
		if (!res)
			return (NULL);
		res->node_type = AST_SIMPLE_COMMAND;
		res->token = NULL;
		res->left = (t_ast *) malloc(sizeof(t_ast));
		if (!res->left)
		{
			free(res);
			return (NULL);
		}
		res->left->node_type = AST_COMMAND_NAME;
		res->left->token = *cursor;
		res->left->left = NULL;
		res->left->right = NULL;
		if (*cursor)
			*cursor = (*cursor)->next;
		if (!*cursor || (*cursor)->type == TOKEN_SEMICOLON)
		{
			res->right = NULL;
		}
	}
	return (res);
}

int	complete_command(t_ast ***tree_list, t_token **cursor, size_t idx)
{
	t_token *reset;

	reset = *cursor;
	(*tree_list)[idx] = (t_ast *) malloc(sizeof(t_ast));
	if (!(*tree_list)[idx])
		return (0);
	((*tree_list)[idx])->node_type = AST_COMPLETE_COMMAND;
	((*tree_list)[idx])->token = NULL;
	((*tree_list)[idx])->right = NULL;

	((*tree_list)[idx])->left = simple_command(cursor, reset);
	if (!((*tree_list)[idx])->left)
		return (0);
	//if we have a simple_command, and tokens left, we also need to check if it's the start of a pipe_sequence
	if (*cursor)
		;//check pipe_sequence and return 0 if fails
	return (1);
}

t_ast	**construct_ast_list(t_token **cursor)
{
	t_token *reset;
	t_ast	**tree_list;
	size_t	idx;

	reset = *cursor;
	//tree list will be a null-terminated array of pointers to root-ast nodes
	//We can determine this by counting the occurences of TOKEN_SEMICOLON
	tree_list = (t_ast **) ft_memalloc(sizeof(t_ast *) * (token_semicolon_count(*cursor) + 1));
	if (!tree_list)
		return (NULL);
	//loop through tokens until either we reach the end or encounter a sequence not matching grammar
	idx = 0;
	while (*cursor && complete_command(&tree_list, cursor, idx))
	{
		idx++;
		if (*cursor)
			*cursor = (*cursor)->next;
	}
	//if we get to here and we're not at the end of the token list, something has gone wrong
	//free everything!!!!!
	if (*cursor)
		return (NULL);
	return (tree_list);
}

