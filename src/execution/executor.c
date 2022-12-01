/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/01 12:35:38 by jumanner         ###   ########.fr       */
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
		return (exit_if_forking(forking,
				built_in_run(built_in_get(args[0]), args, state, ast)));
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

pid_t	execute(char *const *args, t_state *state, t_ast_context *ast)
{
	bool	forking;
	pid_t	fork_result;

	if (args && !args[0])
		return (-1);
	if (!args || !(args[0]))
		return (print_error(-1, ETEMPLATE_SHELL_SIMPLE, ERR_MALLOC_FAIL));
	forking = (in_pipes(ast->pipes) || !built_in_get(args[0]));
	if (forking)
	{
		fork_result = start_fork(ast);
		if (fork_result == -1)
			return (print_error(-1, ETEMPLATE_SHELL_SIMPLE,
					ERR_CHILD_PROC_FAIL));
		else if (fork_result != 0)
			return (fork_result);
	}
	return (execute_child(args, state, ast, forking));
}
