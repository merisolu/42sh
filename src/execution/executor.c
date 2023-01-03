/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/03 11:51:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	execute_absolute_path(char *const *args, t_state *state)
{
	int	return_value;

	return_value = check_path_validity(args[0]);
	if (return_value != 0)
		return (return_value);
	if (!env_set("_", args[0], &(state->env)))
		return (1);
	bin_execve(args[0], (char **)args, state->env);
	return (0);
}

static pid_t	exit_if_forking(bool forking, int return_value)
{
	if (forking)
		exit((pid_t) return_value);
	return ((pid_t) return_value);
}

static pid_t	execute_child(char *const *args, t_state *state, \
t_ast_context *ast, bool forking)
{
	char	*path;
	pid_t	return_value;

	if (built_in_get(args[0]))
	{
		if (forking)
			return (exit_if_forking(forking,
					built_in_run(built_in_get(args[0]), args, state, ast)));
		built_in_run(built_in_get(args[0]), args, state, ast);
		return (exit_if_forking(forking, 0));
	}
	if (ft_strchr(args[0], '/') || (args[0][0] == '.'))
		return (exit_if_forking(forking, execute_absolute_path(args, state)));
	return_value = find_from_path(args[0], state->env, &path);
	if (return_value != 1)
		return (exit_if_forking(forking, return_value));
	return_value = env_set("_", path, &(state->env));
	if (return_value)
		bin_execve(path, (char **)args, state->env);
	free(path);
	return (exit_if_forking(forking, return_value));
}

/*
 * If variables are declared at the start of a command, these should be
 * temporarily added to the environment for that command. After the commmand
 * has finished executing these will be removed.
 *
 * The while loop is basically lifted straight out of the env builtin.
 * We know at this point the parser has validated the var_list, we can just do
 * a little pointer magic and let env_set take care of updating the env array.
 */

bool	update_env(t_state *state, t_ast_context *ctx)
{
	char	**var_list;
	char	*pair;
	char	*temp;
	int		i;

	if (!ctx->node->left->var_list)
		return (true);
	var_list = ctx->node->left->var_list;
	i = 0;
	while (var_list[i])
	{
		pair = var_list[i];
		temp = ft_strchr(pair, '=') + 1;
		pair[ft_dstchr(pair, '=', ft_strlen(pair))] = '\0';
		if (!env_set(pair, temp, &(state->env)))
			return (false);
		i++;
	}
	return (true);
}

pid_t	execute(char *const *args, t_state *state, t_ast_context *ast)
{
	bool	forking;
	pid_t	fork_result;

/*	if (args && !args[0])
		return (-1);
	if (!args || !(args[0]))
		return (print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));*/
	if (!update_env(state, ast))
		return (-1);
	forking = (in_pipes(ast->pipes) || !built_in_get(args[0]));
	if (forking)
	{
		fork_result = start_fork(ast);
		if (fork_result == -1)
			return (-1);
		else if (fork_result != 0)
			return (fork_result);
	}
	return (execute_child(args, state, ast, forking));
}
