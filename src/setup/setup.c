/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:21:45 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/29 15:35:31 by amann            ###   ########.fr       */
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

	ft_dup_null_array((void **)*env, (void ***)&(result->env), var_copy);
	result->exported = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2));
	result->intern = (char **) ft_memalloc(sizeof(char *) * (INPUT_MAX_SIZE / 2));
	if (!(result->intern) || !(result->exported) || !(result->env))
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	return (env_unset("OLDPWD", &(result->env)));
}

int	setup(char *const **env, t_state *state)
{
	char	*term;
	int		database_result;

	if (!get_state_struct(env, state) || !set_shlvl(&(state->env)))
		return (0);
	term = getenv("TERM");
	if (!term)
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_ENV_MISSING_TERM));
	database_result = tgetent(NULL, term);
	if (database_result < 0)
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_TERMCAP_NO_ACCESS));
	else if (database_result == 0)
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_TERMCAP_NO_ENTRY));
	if (state->input_context.width == 0 || state->input_context.height == 0)
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_WINDOW_TOO_SMALL));
	if (!terminal_get_configs(&(state->input_conf), &(state->orig_conf)))
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	if (!terminal_apply_config(&(state->input_conf)))
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_TERMIOS_FAIL));
	state->terminal_conf_applied = true;
	history_load(state);
	set_signal_handling();
	save_cursor(&(state->input_context));
	display(&(state->input_context), 1);
	return (1);
}
