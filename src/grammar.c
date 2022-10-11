/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:23:36 by amann             #+#    #+#             */
/*   Updated: 2022/10/11 14:09:58 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	separator(t_token **cursor, t_token *reset)
{
	if ((*cursor)->type == TOKEN_SEMICOLON || (*cursor)->type == TOKEN_NEWLINE)
	{
		*cursor = (*cursor)->next;
		return (TRUE);
	}
	*cursor = reset;
	return (FALSE);
}

int	cmd_name(t_token **cursor, t_token *reset)
{
	if (expect_token(cursor, TOKEN_WORD, reset))
	{
		while ((*cursor)->type == TOKEN_WORD)
			*cursor = (*cursor)->next;
		return (TRUE);
	}
	return (FALSE);
}

int	simple_command(t_token **cursor, t_token *reset)
{
	return (cmd_name(cursor, reset));
}

int	pipe_sequence(t_token **cursor, t_token *reset)
{
	if (simple_command(cursor, reset))
	{
		*cursor = (*cursor)->next;
		if (!(*cursor))
			return (TRUE);
		if ((*cursor)->type == TOKEN_PIPE)
		{
			*cursor = (*cursor)->next;
			if (simple_command(cursor, reset))
				return (TRUE);
			return (FALSE);
		}
	}
	return (FALSE);
}

int	complete_command(t_ast ***tree_list, t_token **cursor, size_t idx)
{
	t_token *reset;

	reset = *cursor;
	(*tree_list)[idx] = (t_ast *) malloc(size_of(t_ast));
	if (!(*tree_list)[idx])
		return (0);



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
	tree_list = (t_ast **) malloc(sizeof(t_ast *) * token_semicolon_count(*cursor));
	if (!tree_list)
		return (NULL);
	//loop through tokens until either we reach the end or encounter a sequence not matching grammar
	idx = 0;
	while (*cursor && complete_command(&tree_list, cursor, idx))
	{
		idx++;
		*cursor = (*cursor)->next;
	}
	//if we get to here and we're not at the end of the token list, something has gone wrong
	//free everything!!!!!
	if (*cursor)
		return (NULL);
	return (tree_list);
}

