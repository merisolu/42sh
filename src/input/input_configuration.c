/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_configuration.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:20:24 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 12:53:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	set_input_config(t_state *state)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &(state->input_conf)) == -1)
		return (0);
	return (1);
}

int	set_orig_config(t_state *state)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &(state->orig_conf)) == -1)
		return (0);
	return (1);
}

/*
 * Configures the terminal input with the following settings:
 * - Enables continuous input from STDIN (O_NONBLOCK).
 * - Disables input canonicalization and echoing (ICANON and ECHO).
 * - Enables signal generation (ISIG).
 * 
 * The original termios struct is stored in state->orig_conf, and the new one
 * in state->input_conf. Similarly state->orig_flags is set to the earlier fcntl
 * flags and the new ones are stored in state->input_flags.
 * 
 * At the end of the function, set_input_config() is called to set the proper
 * input state for the shell.
 * 
 * Returns 1 on success, 0 on error.
 */
int	configure_input(t_state *state)
{
	if (tcgetattr(STDIN_FILENO, &(state->input_conf)) == -1)
		return (0);
	state->orig_conf = state->input_conf;
	state->input_conf.c_lflag &= ~(ICANON | ECHO);
	state->input_conf.c_lflag |= ISIG;
	state->input_conf.c_cc[VMIN] = 0;
	state->input_conf.c_cc[VTIME] = 1;
	state->input_conf.c_cc[CC_SUSPEND] = '\0';
	return (set_input_config(state));
}
