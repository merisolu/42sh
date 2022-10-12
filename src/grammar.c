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

void	realloc_array(char ***arr, size_t size)
{
	char	**res;
	size_t	i;


	res = (char **) ft_memalloc(sizeof(char *) * (size + 1));
	//malloc protect
	i = 0;
	while ((*arr)[i])
	{
		res[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = res;
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
	if (*cursor && (*cursor)->type == TOKEN_WORD)
		return (TRUE);
	return (FALSE);
}

t_ast	*cmd_suffix(t_token **cursor)
{
	t_ast	*res;
	size_t	size;
	size_t	idx;
	size_t	args;

	if (!*cursor || (*cursor)->type == TOKEN_SEMICOLON || (*cursor)->type == TOKEN_PIPE)
		return (NULL);
	res = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!res)
		return (NULL);
	res->node_type = AST_COMMAND_SUFFIX;
	res->left = NULL;
	res->right = NULL;
	res->token = NULL;
	size = 2;
	idx = 0;
	args = FALSE;
	res->arg_list = (char **) ft_memalloc(sizeof(char *) * (size + 1));
	while (*cursor)
	{
		if ((*cursor)->type == TOKEN_SEMICOLON || (*cursor)->type == TOKEN_PIPE)
			return (res);
		if ((*cursor)->type == TOKEN_WORD)
		{
			if (!args)
				args = TRUE;
			if (idx >= size)
			{
				size *= 2;
				realloc_array(&(res->arg_list), size);
			}
			ft_printf("%s %zu %zu\n",(*cursor)->value, size + 1, idx);
			res->arg_list[idx] = ft_strdup((*cursor)->value);
			idx++;
		}
		*cursor = (*cursor)->next;
	}
	if (!args)
	{
		free(res->arg_list);
		free(res);
		return (NULL);
	}
	return (res);
}

t_ast	*simple_command(t_token **cursor, t_token *reset)
{
	t_ast	*res;

	res = NULL;
	if (cmd_name(cursor, reset))
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
		res->left->node_type = AST_COMMAND_NAME;
		res->left->token = *cursor;
		if (*cursor)
			*cursor = (*cursor)->next;
		res->right = cmd_suffix(cursor);
		//if (!res->right)
		//.	return (NULL);
	}
	return (res);
}

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

t_ast	*pipe_sequence(t_token **cursor)
{
	t_ast	*new_node;
	t_token *reset;

	reset = *cursor;
	ft_printf("the cursor points to: %s\n", reset->value);
	new_node = (t_ast *) ft_memalloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->node_type = AST_PIPE_SEQUENCE;
	new_node->left = simple_command(cursor, reset);
	if (!(new_node->left))
		return (NULL);
	if (*cursor && (*cursor)->type == TOKEN_SEMICOLON)
		return (new_node);
	if (!(*cursor))
		return (new_node);
	*cursor = (*cursor)->next;
	//if next command ends with a pipe, we need to create a new pipesequence
	if (*cursor && pipes_in_queue(*cursor))
		new_node->right = pipe_sequence(cursor);
	//otherwise, the right node can be a command
	else if (*cursor)
		new_node->right = simple_command(cursor, reset);
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
		ft_printf("%zu\n", idx);
		tree_list[idx] = pipe_sequence(cursor);
		idx++;
		if (*cursor)
		{
			ft_printf("this is the cursor in the loop: %s\n", (*cursor)->value);
			*cursor = (*cursor)->next;
		}
	}
	//if we get to here and we're not at the end of the token list, something has gone wrong
	//free everything!!!!!
	//if (*cursor)
	//	return (NULL);
	return (tree_list);
}

