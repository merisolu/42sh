/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_configuration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:21:26 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 17:48:48 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int	terminal_apply_config(struct termios *config)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, config) == -1)
		return (0);
	return (1);
}

/*
 * Configures the terminal with the following settings:
 * - Enables continuous input from STDIN (O_NONBLOCK).
 * - Disables input canonicalization and echoing (ICANON and ECHO).
 * - Enables signal generation (ISIG).
 *
 * The original termios struct is stored in *original, and the new one
 * in *input.
 *
 * Returns 1 on success, 0 on error.
 */

int	terminal_get_configs(struct termios *input, struct termios *original)
{
	if (tcgetattr(STDIN_FILENO, input) == -1)
		return (0);
	*original = *input;
	input->c_lflag &= ~(ICANON | ECHO);
	input->c_lflag |= ISIG;
	input->c_cc[VMIN] = 0;
	input->c_cc[VTIME] = 1;
	input->c_cc[CC_SUSPEND] = '\0';
	return (1);
}
