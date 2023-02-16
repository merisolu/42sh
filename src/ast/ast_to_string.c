/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:43:00 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/16 11:14:46 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void	add_redirections(t_ast_redir **redirs, char **result)
{
	size_t	i;

	i = 0;
	while (redirs[i] && *result)
	{
		if (redirs[i]->aggregation)
		{
			*result = ast_string_builder_int(
					*result, redirs[i]->agg_from, true);
			if (*result)
				*result = ft_strjoinfree(*result, ">&");
			if (*result && redirs[i]->agg_close)
				*result = ft_strjoinfree(*result, "-");
			else if (*result)
				*result = ast_string_builder_int(
						*result, redirs[i]->agg_to, false);
		}
		else
		{
			*result = ast_string_builder(*result, redirs[i]->redir_op);
			if (*result)
				*result = ft_strjoinfree(*result, redirs[i]->redir_file);
		}
		i++;
	}
}

static void	add_vars_and_args(char **vars, char **args, char **result)
{
	size_t	i;

	i = 0;
	while (vars[i] && *result)
	{
		*result = ast_string_builder(*result, vars[i]);
		i++;
	}
	i = 0;
	while (args[i] && *result)
	{
		*result = ast_string_builder(*result, args[i]);
		i++;
	}
}

static void	add_simple_command(t_ast *ast, char **result)
{
	if (ast->left && ast->left->arg_list)
		add_vars_and_args(ast->left->var_list, ast->left->arg_list, result);
	if (*result && ast->right && ast->right->redirs)
		add_redirections(ast->right->redirs, result);
}

static void	add_pipe_sequence(t_ast *ast, char **result)
{
	if (ast->left)
	{
		if (ast->left->node_type == AST_PIPE_SEQUENCE)
			add_pipe_sequence(ast->left, result);
		else if (*result && ast->left->node_type == AST_SIMPLE_COMMAND)
			add_simple_command(ast->left, result);
	}
	if (*result && ast->right)
	{
		*result = ast_string_builder(*result, "|");
		if (*result && ast->right->node_type == AST_PIPE_SEQUENCE)
			add_pipe_sequence(ast->right, result);
		else if (*result && ast->right->node_type == AST_SIMPLE_COMMAND)
			add_simple_command(ast->right, result);
	}
}

char	*ast_to_string(t_ast *ast)
{
	char	*result;

	result = ft_strnew(1);
	add_pipe_sequence(ast, &result);
	return (result);
}
