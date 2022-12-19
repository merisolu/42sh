/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:06:38 by amann             #+#    #+#             */
/*   Updated: 2022/12/19 11:44:13 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static bool	exp_redirs_loop(t_ast *root, t_state *state)
{
	int	i;

	i = 0;
	while (root->redirs[i])
	{
		if (!expand_node(&(root->redirs[i]->redir_file), state))
			return (false);
		i++;
	}
	return (true);
}

static bool	exp_args_loop(t_ast *root, t_state *state)
{
	int	i;

	i = 0;
	while (root->arg_list[i])
	{
		if (!expand_node(&(root->arg_list[i]), state))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_expansions(t_ast *root, t_state *state)
{
	if (!root)
		return (true);
	if (!parse_expansions(root->right, state))
		return (false);
	if (root->node_type == AST_COMMAND_ARGS)
		return (exp_args_loop(root, state));
	if (root->node_type == AST_REDIRECTIONS && root->redirs)
		return (exp_redirs_loop(root, state));
	if (!parse_expansions(root->left, state))
		return (false);
	return (true);
}
