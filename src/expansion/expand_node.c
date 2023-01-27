/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:18:51 by amann             #+#    #+#             */
/*   Updated: 2023/01/27 17:48:28 by amann            ###   ########.fr       */
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

void	expansions_loop(t_token **cursor, t_state *state, char **result, bool recurs)
{
	int		func_result;
	t_token *head;

	if (!recurs)
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
	}
	if (!recurs)
		token_list_free(&head);
	return ;
}

bool	expand_node(char **word, t_state *state)
{
	t_token	*list;
	char	*result;

	if (!*word)
		return (true);
	list = expansions_retokenize(*word);
//	ft_printf("list orig: %p\n", list);
	if (!list)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	//print_tokens(list);
	result = NULL;
//	head = list;
//	ft_printf("1 head %p list %p\n", head, list);
	expansions_loop(&list, state, &result, false);
//	ft_printf("2 head %p list %p\n", head, list);
	//ft_putendl("head tokens:");
//	token_list_free(&head);
//	ft_printf("3 head %p list %p\n", head, list);
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
