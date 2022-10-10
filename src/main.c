/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/10 11:56:05 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_last_signal;

static int	get_state_struct(char *const **env, t_state *result)
{
	size_t	i;

	i = 0;
	ft_bzero(result, sizeof(t_state));
	result->input = ft_memalloc(INPUT_MAX_SIZE + 1);
	if (!result->input)
		return (0);
	result->clipboard = ft_memalloc(INPUT_MAX_SIZE + 1);
	if (!result->clipboard)
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

static void	tokenize_and_execute(t_state *state)
{
	char		**args;

	if (ft_strisempty(state->input))
	{
		clear_input(state, 1);
		return ;
	}
	if (!set_orig_config(state))
	{
		print_error(ERR_TERMIOS_FAIL, 1);
		return ;
	}
	history_store(state->input, state);
	state->cursor = ft_strlen(state->input);
	ft_putchar('\n');
	args = parse(tokenize(state->input), state);
	set_return_value(execute(args, state), state);
	if (args)
		env_set("_", args[ft_null_array_len((void **)args) - 1], &(state->env));
	ft_free_null_array((void **)args);
	clear_input(state, 0);
	if (!set_input_config(state))
		print_error(ERR_TERMIOS_FAIL, 1);
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
	if (!configure_input(state))
		return (print_error(ERR_TERMIOS_FAIL, 0));
	if (!set_shlvl(&(state->env)))
		return (0);
	set_signal_handling();
	save_cursor(state);
	print_state(state);
	return (1);
}

static int	cleanup(t_state *state)
{
	if (!set_orig_config(state))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	ft_free_array_elements((void **)state->history, HISTORY_SIZE);
	ft_free_null_array((void **)(state->env));
	free(state->input);
	free(state->clipboard);
	return (state->exit_return_value);
}

int	main(const int argc, const char **argv, char *const *env)
{
	t_state		state;

	(void)argc;
	(void)argv;
	if (!setup(&env, &state))
		return (1);
	while (!state.exiting)
	{
		check_signal(&state);
		if (get_input(&state) == INPUT_NEWLINE_FOUND)
		{
			tokenize_and_execute(&state);
			if (!state.exiting)
			{
				if (g_last_signal != 0 && state.last_return_value > 128)
					ft_putchar('\n');
				save_cursor(&state);
				print_state(&state);
			}
			g_last_signal = 0;
		}
	}
	ft_putendl("exit");
	return (cleanup(&state));
}
