/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/04 15:48:07 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_last_signal;

static int	get_state_struct(char *const **env, t_state *result)
{
	size_t	i;

	i = 0;
	ft_bzero(result, sizeof(t_state));
	if (!input_context_set(&(result->input_context), "\n"))
		return (0);
	while (i < HISTORY_SIZE)
	{
		result->history[i] = ft_memalloc(INPUT_MAX_SIZE + 1);
		if (!result->history[i])
			return (0);
		i++;
	}
	if (!ft_dup_null_array((void **)*env, (void ***)&(result->env), var_copy))
		return (0);
	return (
		env_unset("OLDPWD", &(result->env))
	);
}

static int	setup(char *const **env, t_state *state)
{
	char	*term;
	int		database_result;

	term = getenv("TERM");
	if (!term)
		return (print_error(ERR_ENV_MISSING_TERM, 0));
	database_result = tgetent(NULL, term);
	if (database_result < 0)
		return (print_error(ERR_TERMCAP_NO_ACCESS, 0));
	else if (database_result == 0)
		return (print_error(ERR_TERMCAP_NO_ENTRY, 0));
	if (!get_state_struct(env, state))
		return (print_error(ERR_MALLOC_FAIL, 0));
	if (state->input_context.width == 0 || state->input_context.height == 0)
		return (print_error(ERR_WINDOW_TOO_SMALL, 0));
	if (!configure_terminal(state))
		return (print_error(ERR_TERMIOS_FAIL, 0));
	if (!set_shlvl(&(state->env)))
		return (0);
	set_signal_handling();
	save_cursor(&(state->input_context));
	display(&(state->input_context));
	return (1);
}

static int	cleanup(t_state *state, int return_value)
{
	if (!set_orig_config(state))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	ft_free_array_elements((void **)state->history, HISTORY_SIZE);
	ft_free_null_array((void **)(state->env));
	input_context_free(&(state->input_context));
	return (return_value);
}

static t_input_result	get_input(t_state *state)
{
	t_input_result	result;

	result = get_line(&(state->input_context), 0);
	if (result == INPUT_NO_MARK_FOUND)
		display(&(state->input_context));
	if (result == INPUT_MARK_FOUND)
		return (INPUT_MARK_FOUND);
	else if (result == INPUT_READ_ERROR)
		return (print_error(ERR_LINE_READ, 1));
	return (result);
}

int	main(const int argc, const char **argv, char *const *env)
{
	t_state	state;

	(void)argc;
	(void)argv;
	if (!setup(&env, &state))
		return (cleanup(&state, 1));
	while (!state.exiting)
	{
		check_signal(&state);
		if (get_input(&state) == INPUT_MARK_FOUND)
		{
			tokenize_and_execute(&state);
			if (!state.exiting)
			{
				if (g_last_signal != 0 && state.last_return_value > 128)
					ft_putchar('\n');
				save_cursor(&(state.input_context));
				display(&(state.input_context));
			}
			g_last_signal = 0;
		}
	}
	ft_putendl("exit");
	return (cleanup(&state, state.exit_return_value));
}
