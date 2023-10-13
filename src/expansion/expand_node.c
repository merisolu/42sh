/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:18:51 by amann             #+#    #+#             */
/*   Updated: 2023/02/15 18:12:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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

void	expansions_loop(t_token **cursor, t_state *state, char **result, bool r)
{
	int		func_result;
	t_token	*head;

	if (!r)
		head = *cursor;
	while (*cursor)
	{
		func_result = run_functions(cursor, state, result);
		if (func_result == 0 && *cursor)
		{
			func_result = add_to_result(result, (*cursor)->value, state);
			*cursor = (*cursor)->next;
		}
		if (func_result == -1)
			free(*result);
		if (!(state->t.in_braces) && r)
			break ;
	}
	if (!r)
		token_list_free(&head);
	return ;
}

static bool	malloc_err(t_state *state)
{
	if (!(state->t.autocomp))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	return (false);
}

bool	expand_node(char **word, t_state *state, bool autocomp)
{
	t_token		*token_list;
	char		*result;

	if (!*word)
		return (true);
	ft_bzero((void *)&(state->t), sizeof(state->t));
	state->t.expansion_word = *word;
	state->t.autocomp = autocomp;
	token_list = expansions_retokenize(*word);
	if (!token_list)
		return (malloc_err(state));
	result = NULL;

	// quote and backslash handling should happen before the expansions_loop
	// un-closed quotes are checked by input process to handle newlines.
	// Therefore, it should be safe to re-categorise tokens inside quotes
	// based on the quote type
	// With backslash, it should be ok to just change the type of the
	// subsequent token - thereby 'escaping' it before the expansions_loop

	expansions_loop(&token_list, state, &result, false);
	reset_state(state);
	if (!result)
		return (false);
	if (ft_strequ(*word, result))
	{
		free(result);
		return (true);
	}
	ft_strdel(word);
	*word = result;
	return (true);
}
