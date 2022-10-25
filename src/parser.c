/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:11:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/25 12:44:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	add_to_result(char **res, char *value, t_state *state)
{
	char	*temp;

//	ft_printf("res = %s | value = %s\n", *res, value);
	if (!value)
		return (-1);
	if (state->continue_previous_node)
	{
		temp = ft_strjoin(*res, value);
		if (!temp)
			return (-1);
		ft_strdel(res);
		*res = ft_strdup(temp);
		free(temp);
		if (!(*res))
			return (-1);
		return (1);
	}
	else
	{
		state->continue_previous_node = 1;
		ft_strdel(res);
		*res = ft_strdup(value);
		if (!(*res))
			return (-1);
		return (1);
	}
	return (-1);
}

void	reset_state(t_state *state)
{
	if (!state)
		return ;
	state->continue_previous_node = 0;
	state->in_assignment = 0;
	state->has_seen_tilde_in_word = 0;
	state->in_double_quotes = 0;
}

void	clense_ws(t_token **list)
{
	t_token	*cursor;
	t_token	*temp;

	cursor = *list;
	while (cursor)
	{
		if (cursor->type == TOKEN_WHITESPACE)
		{
			if (cursor->previous == NULL)
				temp = cursor->next;
			else if (cursor->next == NULL)
				temp = NULL;
			else
			{
				cursor->previous->next = cursor->next;
				cursor->next->previous = cursor->previous;
				temp = cursor->next;
			}
			free(cursor->value);
			free(cursor);
			cursor = temp;
		}
		else
			cursor = cursor->next;
	}
}

t_ast	**parse(t_token *list, t_state *state)
{
	t_ast	**tree;
	int		i;

	if (!list || !state)
		return (NULL);
	reset_state(state);
	clense_ws(&list); // this could potentially be moved into the lexer
	tree = construct_ast_list(&list);
	token_list_free(&list);
	if (!tree)
		return (NULL);
	//print_ast(tree);
	i = 0;
	while (tree[i])
	{
		if (!ast_parse_expansions(tree[i], state))
		{
			ast_free(tree);
			return (NULL);
		}
		i++;
	}
	return (tree);
}
/*
 * print_ast(tree);
 * Parses the given list of tokens, handles expansions and whitespace, puts the
 * result into a char**, then returns it.
 *
 * Returns NULL on error.


t_ast	**parse(t_token *list, t_state *state)
{
	t_token	*cursor;
	char	**result;
	int		func_result;

	if (!list || !state)
		return (NULL);
	reset_state(state);
	cursor = list;
	result = (char **)ft_memalloc(sizeof(char *));
	while (cursor && result)
	{
		func_result = run_functions(&cursor, state, &result);
		if (func_result == 0 && cursor)
		{
			func_result = add_to_result(&result, cursor->value, state);
			cursor = cursor->next;
		}
		if (func_result == -1)
			result = ft_free_null_array((void **)result);
	}
	if (state->in_double_quotes && add_to_result(&result, "", state) == -1)
		result = ft_free_null_array((void **)result);
	token_list_free(&list);
	for (int i = 0; result[i] != NULL; i++)
	{
		if (ft_strequ(result[i], "exit"))
			exit(0);
		ft_putendl(result[i]);
	}
	return (NULL);
}*/
