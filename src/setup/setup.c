/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:21:45 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/05 14:41:24 by amann            ###   ########.fr       */
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
	return (result);
}

static bool	initialise_arrays(char *const **env, t_state *result)
{
	int		i;
	char	**temp;

	ft_dup_null_array((void **)*env, (void ***)&(result->env), var_copy);
	result->exported = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE));
	result->intern = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE));
	if (!(result->intern) || !(result->exported) || !(result->env))
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	i = 0;
	while ((result->env)[i])
	{
		temp = (char **)&((result->exported)[i]);
		*temp = ft_strdup((result->env)[i]);
		if (!((result->exported)[i]))
			return (print_error_bool(
					false,
					ERRTEMPLATE_SIMPLE,
					ERR_MALLOC_FAIL
				));
		i++;
	}
	return (true);
}

static int	get_state_struct(char *const **env, t_state *result)
{
	size_t	i;
	char	**reserved_sequences;

	i = 0;
	ft_bzero(result, sizeof(t_state));
	ft_bzero(result->pids, sizeof(pid_t) * MAX_PIDS);
	reserved_sequences = get_reserved_sequences();
	if (!reserved_sequences)
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
	return (env_unset("OLDPWD", &(result->env)));
}

bool	setup(char *const **env, t_state *state)
{
	if (!get_state_struct(env, state) || !set_shlvl(&(state->env)))
		return (false);
	if (!setup_fd())
		return (false);
	if (!setup_termcaps())
		return (false);
	if (!setup_input(state))
		return (false);
	history_load(state);
	set_signal_handling();
	save_cursor(&(state->input_context));
	display(&(state->input_context), 1);
	return (true);
}
