/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:11:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/23 13:29:03 by amann            ###   ########.fr       */
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

/*
 * TODO variable ($) and tilde (~) expansions
 * - we cannot expand during tokenisation as this could cause problems during tree construction
 *		- however, this is also where quote handling happens, so doing it elsewhere would make it
 *		tricky/impossible to manage quote inhibition properly.
 * - another option would be to leave the quotes in the strings while the AST is being built. Then
 *   remove them during parsing (only external quotes need to be removed, these would be first and last
 *   chars of each string). This would tell us when not to expand $ and ~
 * - If we do not care about quote inhibition, we can could just parse each word of the arg_list.
 * - We could also re-tokenise each arg_list - this would probably involve strjoin-ing them back together...
 *   probably quite a lot of work to get a sub-optimal result.
 *
 *   The plan
 *   - We need to iterate through to the arg_list and filenames (in_file, out_file) in the AST to
 *   check for expansions
 *   - To handle quotes properly, we need to tweak the tokenizer to make sure they remain in the strings
 *   - We can then remove them in the parsing phase, being mindful of quote inhibition when handling expansions
 *   - Each arg in each arg_list can then be re-tokenised, with a view to retro-fitting the old expansion process
 *   into the new system.
 */
static const t_token_dispatch	*get_parse_token_dispatch(void)
{
	static const t_token_dispatch	dispatch_table[] = {
	{'$', TOKEN_DOLLAR},
	{'~', TOKEN_TILDE},
	{'"', TOKEN_DOUBLE_QUOTE},
	{'\'', TOKEN_SINGLE_QUOTE},
	{'{', TOKEN_CURLY_OPEN},
	{'}', TOKEN_CURLY_CLOSED},
	{'+', TOKEN_PLUS},
	{'-', TOKEN_MINUS},
	{'\0', TOKEN_NULL}
	};

	return (dispatch_table);
}

static t_token_type	get_parser_token_type(char value)
{
	const t_token_dispatch	*dispatch_table;
	size_t					i;

	dispatch_table = get_parse_token_dispatch();
	i = 0;
	while (dispatch_table[i].token != TOKEN_NULL)
	{
		if (dispatch_table[i].symbol == value)
			return (dispatch_table[i].token);
		i++;
	}
	if (ft_is_whitespace(value))
		return (TOKEN_WHITESPACE);
	return (TOKEN_WORD);
}

static t_token	*re_tokenize(char *line)
{
	t_token			*result;
	t_token_type	type;
	int				i;
	int				buff_idx;
	char			*buff;

	buff = ft_strnew(ft_strlen(line) + 1);
	if (!buff)
		return (NULL);
	result = NULL;
	type = get_parser_token_type(line[0]);
	i = 0;
	buff_idx = 0;
	while (line[i])
	{
		if (get_parser_token_type(line[i]) != type)
		{
			token_add(&result, type, ft_strdup(buff));
			ft_bzero(buff, ft_strlen(buff) + 1);
			type = get_parser_token_type(line[i]);
			buff_idx = 0;
		}
		buff[buff_idx] = line[i];
		buff_idx++;
		i++;
	}
	token_add(&result, type, ft_strdup(buff));
	return (result);
}

void	print_tokens(t_token *result)
{
	t_token *temp = result;
	ft_putendl("########## TOKENS ##########");
	while (temp)
	{
		ft_printf("type = %d || value = %s\n", temp->type, temp->value);
		temp = temp->next;
	}
}

static int expand_node(t_ast *node)
{
	int	i;

	if (node->node_type == AST_PIPE_SEQUENCE || node->node_type == AST_SIMPLE_COMMAND)
		return (1);
	if (node->node_type == AST_COMMAND_ARGS)
	{
		i = 0;
		while (node->arg_list[i])
		{
			print_tokens(re_tokenize(node->arg_list[i]));
			ft_putendl(node->arg_list[i++]);
		}
	}
	return (1);
}


int	parse_expansions(t_ast *root)
{
	if (root)
	{
		parse_expansions(root->right);
		if (!expand_node(root))
			return (0);
		parse_expansions(root->left);
	}
	return (1);
}

t_ast	**parse(t_token *list, t_state *state)
{
	t_ast	**tree;
	int		i;

	if (!list || !state)
		return (NULL);
	reset_state(state);
	clense_ws(&list);
	tree = construct_ast_list(&list);
	token_list_free(&list);
	if (!tree)
		return (NULL);
	print_ast(tree);

	i = 0;
	while (tree[i])
	{
		if (!parse_expansions(tree[i]))
		{
			ast_free(tree);
			ft_putendl("you set that tree free");
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
