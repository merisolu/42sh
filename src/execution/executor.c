/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:39:02 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/20 12:47:57 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * Adds path of args[0] to the hash table if its not there. Built-ins are
 * excluded. *path is not freed, as it is stored in the hash table.
 */

static void	update_hash_table(char *const *args, t_state *state)
{
	char	*path;

	if (built_in_get(args[0])
		|| hash_table_get_path(args[0], state->hash_table))
		return ;
	if (!env_get("PATH", state->env)
		|| !env_get("PATH", state->intern))
		return ;
	if (find_binary(args[0], state, &path) == 1)
		hash_table_add(args[0], path, &(state->hash_table), 1);
}

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
	return_value = find_binary(args[0], state, &path);
	if (return_value == 0)
		return (exit_if_forking(forking, print_error(RETURN_COMMAND_NOT_FOUND,
					ERRTEMPLATE_NAMED, args[0], ERR_COM_NOT_FOUND)));
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
	pid_t	pid;
	pid_t	gid;

	if (!update_env_execution(state, ast))
		return (-1);
	forking = (ast->background || in_pipes(ast->pipes)
			|| !built_in_get(args[0]));
	update_hash_table(args, state);
	if (forking)
	{
		pid = start_fork(ast);
		if (pid == -1)
			return (-1);
		else if (pid != 0)
		{
			gid = process_group_set(pid, ast->job->pids[0], (!ast->background));
			if (gid == -1)
				return (-1);
			return (pid);
		}
		if (process_group_set(getpid(), ast->job->pids[0], false) == -1)
			return (-1);
	}
	return (execute_child(args, state, ast, forking));
}
