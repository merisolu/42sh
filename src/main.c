/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/09 11:29:52 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_last_signal;

static int	get_state_struct(char *const **env, t_state *result)
{
	size_t	i;

	i = 0;
	ft_bzero(result, sizeof(t_state));
	if (!input_context_set(&(result->input_context),
			PROMPT, MULTILINE_PROMPT, "\n"))
		return (print_error(ERR_INPUT_CONTEXT_FAIL, 0));
	while (i < HISTORY_SIZE)
	{
		result->history[i] = ft_memalloc(INPUT_MAX_SIZE + 1);
		if (!result->history[i])
			return (print_error(ERR_MALLOC_FAIL, 0));
		i++;
	}
	if (!ft_dup_null_array((void **)*env, (void ***)&(result->env), var_copy))
		return (print_error(ERR_MALLOC_FAIL, 0));
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
		return (0);
	if (state->input_context.width == 0 || state->input_context.height == 0)
		return (print_error(ERR_WINDOW_TOO_SMALL, 0));
	if (!terminal_get_configs(&(state->input_conf), &(state->orig_conf)))
		return (print_error(ERR_TERMIOS_FAIL, 0));
	if (!terminal_apply_config(&(state->input_conf)))
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
	if (!terminal_apply_config(&(state->orig_conf)))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	ft_free_array_elements((void **)state->history, HISTORY_SIZE);
	ft_free_null_array((void **)(state->env));
	input_context_free(&(state->input_context));
	return (return_value);
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
		if (get_input(&(state.input_context)) == INPUT_MARK_FOUND)
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
