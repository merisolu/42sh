/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:18:51 by amann             #+#    #+#             */
/*   Updated: 2023/02/03 13:46:15 by amann            ###   ########.fr       */
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
		if (!(state->in_braces) && r)
			break ;
	}
	if (!r)
		token_list_free(&head);
	return ;
}

static void	reset_state_lexing(t_state *state)
{
	state->in_quotes = false;
	state->in_squotes = false;
	state->in_braces = false;
	state->in_squote_braces = false;
	state->in_dquote_braces = false;
	state->brace_count = 0;
	state->brace_sq_count = 0;
	state->brace_dq_count = 0;
	state->quote_type = 0;
}

bool	expand_node(char **word, t_state *state)
{
	t_token	*list;
	char	*result;

	if (!*word)
		return (true);
	state->expansion_word = *word;
	reset_state_lexing(state);
	list = expansions_retokenize(*word);
	if (!list)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	result = NULL;
	expansions_loop(&list, state, &result, false);
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
