/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:20 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 14:01:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

/* Includes */

# include <sys/ioctl.h>
# include <termcap.h>
# include "libft.h"
# include "general.h"
# include "input.h"

/* Files */

/* error.c */
int		print_error(char *message, int return_value);
int		print_named_error(char *name, char *message, int return_value);

/* return_value.c */
int		get_return_value_from_status(int status);
void	set_return_value(int return_value, t_state *state);

/* utils.c */
void	update_window_size(t_state *state);
void	clear_input(t_state *state, int newline);
void	print_state(t_state *state);
void	*var_copy(void *var);

#endif
