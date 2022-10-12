/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:11:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/12 16:56:20 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
/*
 * Checks if the cursor is currently on a token with the type of 'type'.
 *
 * If it is, the cursor is advanced to (*cursor)->next, and 1 is returned.
 *
 * If not, *cursor is set to on_fail, and 0 is returned. This is also done
 * if cursor or *cursor is NULL.
 *
 * The goal was to have a "chainable function" that could be called repeatedly
 * to check if a set of tokens in a list matches a predetermined set, while also
 * allowing for easy resets to the start of the chain (for immediate checking of
 * another sequence of tokens) without having to handle it in the calling
 * function.
 */
int	expect_token(t_token **cursor, t_token_type type, t_token *on_fail)
{
	int	result;

	if (!cursor || !(*cursor))
	{
		if (cursor)
			*cursor = on_fail;
		return (0);
	}
	result = (*cursor)->type == type;
	if (result)
		(*cursor) = (*cursor)->next;
	else
		(*cursor) = on_fail;
	return (result);
}

/*
 * Adds the given value to the result array.
 *
 * The way the value is added depends on the continue_previous_node flag.
 *		- If it's set to 1, the last string of the result array will have value
 *		appended to it.
 *		- If it's set to 0, a new node will be created in the result array,
 *		with the given value.
 */
int	add_to_result(char ***result, char *value, t_state *state)
{
	char	**destination;
	char	*temp;

	if (!value)
		return (-1);
	if (state->continue_previous_node)
	{
		destination = ((*result) + ft_null_array_len((void **)(*result)) - 1);
		temp = ft_strjoin(*destination, value);
		if (!temp)
			return (-1);
		free(*destination);
		*destination = temp;
		return (1);
	}
	else
	{
		state->continue_previous_node = 1;
		temp = ft_strdup(value);
		if (!temp)
			return (-1);
		if (ft_add_to_null_array((void ***)result, temp))
			return (1);
	}
	return (-1);
}
/*
static int	run_functions(t_token **cursor, t_state *state, char ***result)
{
	int						func_return;
	static t_parse_function	*functions[] = {
		&expand_variable,
		&expand_tilde,
		&check_literals,
		NULL
	};
	size_t					i;

	i = 0;
	while (functions[i] != NULL)
	{
		func_return = (*functions[i])(cursor, state, result);
		if (func_return != 0)
			return (func_return);
		i++;
	}
	return (0);
}
*/
static void	reset_state(t_state *state)
{
	if (!state)
		return ;
	state->continue_previous_node = 0;
	state->in_assignment = 0;
	state->has_seen_tilde_in_word = 0;
	state->in_double_quotes = 0;
}

/* Shiny new parser 8-)
 *
 * Refer to grammar in opengroup
 *
 * Tree struct needed.
 * - Rule from grammar
 * - Token value
 * - left ptr
 * - right ptr
 *
 * Debug method needed to print the AST
*/

static void	print_ast_node(t_ast *node, int space, int count)
{
	ft_putchar('\n');
	for (int i = count; i < space; i++)
		ft_putchar(' ');
	if (node->node_type == AST_PIPE_SEQUENCE)
		ft_putendl("PIPE_SEQUENCE");
	else if (node->node_type == AST_SIMPLE_COMMAND)
		ft_putendl("SIMPLE_COMMAND");
	if (node->node_type == AST_COMMAND_NAME)
		ft_putendl(node->token->value);
	if (node->node_type == AST_COMMAND_SUFFIX)
	{
		for (int i = 0; (node->arg_list)[i]; i++)
			ft_printf("%s ", (char *)(node->arg_list)[i]);
		ft_putchar('\n');
	}
}

static void	tree_iterate(t_ast *root, int space)
{
	int count;

	count = 20;
	if (root)
	{
		space += count;
		tree_iterate(root->right, space);
		print_ast_node(root, space, count);
		tree_iterate(root->left, space);
	}
	else
		return ;
}

static void	print_ast(t_ast **tree)
{
	size_t	idx;
	t_ast	*root;

	ft_putendl("########## AST ##########");
	if (!tree || !(tree[0]))
	{
		ft_putendl("something terrible happened");
		return ;
	}
	idx = 0;
	while (tree[idx])
	{
		root = tree[idx];
		tree_iterate(root, 0);
		ft_printf("The above is tree number %zu\n", idx + 1);
		idx++;
	}
}

void	clense_ws(t_token **list)
{
	t_token	*cursor;
	t_token *temp;
	int		in_quotes;

	in_quotes = FALSE;
	cursor = *list;
	while (cursor)
	{
		ft_printf("%s\n", cursor->value);
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

char	**parse(t_token *list, t_state *state)
{
	reset_state(state);
	if (ft_strequ(list->value, "exit"))
		exit(0);
	clense_ws(&list);
	print_ast(construct_ast_list(&list));
	return (NULL);
}
/*
 * Parses the given list of tokens, handles expansions and whitespace, puts the
 * result into a char**, then returns it.
 *
 * Returns NULL on error.

char	**parse(t_token *list, t_state *state)
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
	return (result);
}*/

