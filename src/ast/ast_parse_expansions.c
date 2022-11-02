/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_expansions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:18:51 by amann             #+#    #+#             */
/*   Updated: 2022/11/02 14:47:07 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	reset_state(t_state *state)
{
	if (!state)
		return ;
	state->continue_previous_node = 0;
}

static int	run_functions(t_token **cursor, t_state *state, char **result)
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

static char	*expansions_loop(t_token *cursor, t_state *state)
{
	char	*result;
	int		func_result;

	result = NULL;
	while (cursor)
	{
		func_result = run_functions(&cursor, state, &result);
		if (func_result == 0 && cursor)
		{
			func_result = add_to_result(&result, cursor->value, state);
			cursor = cursor->next;
		}
		if (func_result == -1)
			free(result);
	}
	return (result);
}

static int	expand_node(char **word, t_state *state)
{
	t_token	*list;
	char	*result;

	if (!*word)
		return (1);
	list = ast_retokenize(*word);
	if (!list)
		return (print_error(ERR_MALLOC_FAIL, 0));
	result = expansions_loop(list, state);
	token_list_free(&list);
	reset_state(state);
	if (!result)
		return (0);
	if (ft_strequ(*word, result))
	{
		free(result);
		return (1);
	}
	ft_strdel(word);
	*word = result;
	return (1);
}

int	ast_parse_expansions(t_ast *root, t_state *state)
{
	int	i;

	if (!root)
		return (1);
	ast_parse_expansions(root->right, state);
	if (root->node_type == AST_COMMAND_ARGS)
	{
		i = 0;
		while (root->arg_list[i])
		{
			if (!expand_node(&(root->arg_list[i]), state))
				return (0);
			i++;
		}
		return (1);
	}
	if (root->node_type == AST_REDIRECTIONS)
	{
		if (!expand_node(&root->in_file, state)
			|| !expand_node(&root->out_file, state))
			return (0);
		return (1);
	}
	ast_parse_expansions(root->left, state);
	return (1);
}
