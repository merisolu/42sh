/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:23:36 by amann             #+#    #+#             */
/* ************************************************************************** */

#include "shell.h"

int		pipes_in_queue(t_token *cursor)
{
	if (cursor->type == TOKEN_PIPE)
		cursor = cursor->next;
	while (cursor)
	{
		if (cursor->type == TOKEN_PIPE)
			return (TRUE);
		cursor = cursor->next;
	}
	return (FALSE);
}

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

int	check_token_type(t_token **cursor, enum e_token_type type)
{
	if (*cursor && (*cursor)->type == type)
		return (TRUE);
	return (FALSE);
}

/*
 * NB: the below process will result in trailing NULL pointers in our args array, maybe this should
 * be tidied up...
 */
int	realloc_array(char ***arr, size_t size)
{
	char	**res;
	size_t	i;


	res = (char **) ft_memalloc(sizeof(char *) * (size + 1));
	if (!res)
	{
		ft_free_null_array((void **) *arr);
		return (0);
	}
	i = 0;
	while ((*arr)[i])
	{
		res[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = res;
	return (1);
}

int	allocate_args_array(char ***res, t_token **cursor)
{
	size_t	idx;
	size_t	size;

	size = 2;
	idx = 0;
	while (*cursor)
	{
		if (check_token_type(cursor, TOKEN_SEMICOLON) || check_token_type(cursor, TOKEN_PIPE))
			return (1);
		if (check_token_type(cursor, TOKEN_WORD))
		{
			if (idx >= size)
			{
				size *= 2;
				if (!realloc_array(res, size))
					return (0);
			}
			(*res)[idx] = ft_strdup((*cursor)->value);
			if (!(*res)[idx])
				return (0);
			idx++;
		}
		*cursor = (*cursor)->next;
	}
	return (1);
}

char	**add_args(t_token **cursor)
{
	char	**res;

	res = (char **) ft_memalloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	if (!(allocate_args_array(&res, cursor)))
	{
		ft_free_null_array((void **)res);
		return (NULL);
	}
	return (res);
}

t_ast	*simple_command(t_token **cursor)
{
	t_ast	*res;

	res = NULL;
	if (check_token_type(cursor, TOKEN_WORD))
	{
		res = (t_ast *) ft_memalloc(sizeof(t_ast));
		if (!res)
			return (NULL);
		res->node_type = AST_SIMPLE_COMMAND;
		res->left = (t_ast *) ft_memalloc(sizeof(t_ast));
		if (!res->left)
		{
			free(res);
			return (NULL);
		}
		res->left->node_type = AST_COMMAND_ARGS;
		res->left->token = *cursor;
		res->left->arg_list = add_args(cursor);
//		TO-DO - check redirections - right node should contain type of redirect and filename
		res->right = NULL;
	}
	return (res);
}

t_ast	*pipe_sequence(t_token **cursor)
{
	t_ast	*new_node;

	new_node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->node_type = AST_PIPE_SEQUENCE;
	new_node->left = simple_command(cursor);
	if (!(new_node->left))
		return (NULL);
	if (*cursor && check_token_type(cursor, TOKEN_SEMICOLON))
		return (new_node);
	if (!(*cursor))
		return (new_node);
	*cursor = (*cursor)->next;
	//if next command ends with a pipe, we need to create a new pipesequence
	if (*cursor && pipes_in_queue(*cursor))
		new_node->right = pipe_sequence(cursor);
	//otherwise, the right node can be a command
	else if (*cursor)
		new_node->right = simple_command(cursor);
	return (new_node);
}

t_ast	**construct_ast_list(t_token **cursor)
{
	t_token *reset;
	t_ast	**tree_list;
	size_t	len;
	size_t	idx;

	reset = *cursor;
	len = token_semicolon_count(*cursor);
	//tree list will be a null-terminated array of pointers to root-ast nodes
	//We can determine this by counting the occurences of TOKEN_SEMICOLON
	tree_list = (t_ast **) ft_memalloc(sizeof(t_ast *) * (len + 1));
	if (!tree_list)
		return (NULL);
	//loop through tokens until either we reach the end or encounter a sequence not matching grammar
	idx = 0;
	while (idx < len)//*cursor)
	{
		tree_list[idx] = pipe_sequence(cursor);
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

