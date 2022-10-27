/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:11:55 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 10:36:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	continue_word(char **res, char *value)
{
	char	*temp;

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

int	add_to_result(char **res, char *value, t_state *state)
{
	if (!value)
		return (-1);
	if (state->continue_previous_node)
		return (continue_word(res, value));
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
	state->in_double_quotes = 0;
}

t_ast	**parse(t_token *list, t_state *state)
{
	t_ast	**tree;
	int		i;

	if (!list || !state)
		return (NULL);
	reset_state(state);
	ast_cleanse_ws(&list);
	tree = construct_ast_list(&list);
	token_list_free(&list);
	if (!tree)
		return (NULL);
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
