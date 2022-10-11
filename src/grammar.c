/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:23:36 by amann             #+#    #+#             */
/*   Updated: 2022/10/11 18:48:33 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	realloc_array(char ***arr, size_t size)
{
	char	**res;
	size_t	i;


	res = (char **) ft_memalloc(sizeof(char *) * (size + 1));
	//malloc protect
	i = 0;
	while (i < size)
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
	if ((*cursor)->type == TOKEN_WORD)
		return (TRUE);
	return (FALSE);
}

t_ast	*cmd_suffix(t_token **cursor)
{
	t_ast	*res;
	size_t	size;
	size_t	idx;
	size_t	args;

	if (!*cursor || (*cursor)->type == TOKEN_SEMICOLON)
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
			break ;
		if ((*cursor)->type == TOKEN_WORD)
		{
			if (!args)
				args = TRUE;
			if (idx > size)
			{
				size *= 2;
				realloc_array(&(res->arg_list), size);
			}
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
		res->right = cmd_suffix(cursor);
		//if (!res->right)
		//.	return (NULL);
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

