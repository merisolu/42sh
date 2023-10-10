/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:21:45 by jumanner          #+#    #+#             */
/*   Updated: 2023/10/10 15:50:44 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

static char	**get_reserved_sequences(void)
{
	char	**result;

	result = ft_memalloc(sizeof(char **));
	if (!result)
		return (NULL);
	ft_add_to_null_array((void ***)&result, var_copy(ARROW_UP));
	if (!result)
		return (NULL);
	ft_add_to_null_array((void ***)&result, var_copy(ARROW_DOWN));
	if (!result)
		return (NULL);
	ft_add_to_null_array((void ***)&result, var_copy(TAB));
	if (!result)
		return (NULL);
	ft_add_to_null_array((void ***)&result, var_copy(CTRL_R));
	return (result);
}

static bool	initialise_jobs(t_state *state)
{
	ft_bzero(state->jobs, sizeof(t_job) * MAX_JOBS);
	return (true);
}

static bool	initialise_arrays(char *const **env, t_state *result)
{
	result->env = (char **) ft_memalloc(sizeof(char *) * (VAR_MAX));
	result->exported = (char **) ft_memalloc(sizeof(char *) * (VAR_MAX));
	result->intern = (char **) ft_memalloc(sizeof(char *) * (VAR_MAX));
	if (!(result->intern) || !(result->exported) || !(result->env))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	ft_copy_null_array((void **)(result->env), (void **)*env, var_copy);
	ft_copy_null_array((void **)(result->exported), (void **)*env, var_copy);
	return (initialise_jobs(result));
}

static int	get_state_struct(char *const **env, t_state *result)
{
	size_t	i;
	char	**reserved_sequences;

	i = 0;
	ft_bzero(result, sizeof(t_state));
	result->group_id = getpid();
	reserved_sequences = get_reserved_sequences();
	if (!reserved_sequences)
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	if (!hash_table_setup(&(result->hash_table)))
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	if (!input_context_set(&(result->input_context),
			&(t_input_initializer){
			PROMPT, MULTILINE_PROMPT, "\n", reserved_sequences}))
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_INPUT_CONTEXT_FAIL));
	while (i < HISTORY_SIZE)
	{
		result->history[i] = ft_memalloc(INPUT_MAX_SIZE + 1);
		if (!result->history[i])
			return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
		i++;
	}
	if (!initialise_arrays(env, result))
		return (0);
	return (1);
}

bool	setup(char *const **env, t_state *state, bool stdin)
{
	if (!get_state_struct(env, state) || !set_shlvl(&(state->env)))
		return (false);
	if (stdin)
		state->reading_from_stdin = true;
	if (!(state->reading_from_stdin) && !setup_fd())
		return (false);
	if (!(state->reading_from_stdin) && !setup_termcaps())
		return (false);
	if (!(state->reading_from_stdin) && !setup_input(state))
		return (false);
	history_load(state);
	set_signal_handling();
	save_cursor(&(state->input_context));
	if (!(state->reading_from_stdin))
		display(&(state->input_context), 1);
	if (setpgid(getpid(), getpid()) == -1
		|| ioctl(STDIN_FILENO, TIOCSPGRP, &(state->group_id)) == -1)
		return (false);
	delete_var("OLDPWD", &(state->env));
	return (true);
}
