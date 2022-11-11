/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:43:34 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/03 11:58:12 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURSOR_H
# define CURSOR_H

/* Includes */

# include <termcap.h>

# include "libft.h"
# include "general.h"
# include "input.h"
# include "utils.h"

/* Files */

/* cursor.c */
void	save_cursor(t_input_context *state);
void	load_cursor(t_input_context *state);

/* cursor_utils.c */
void	move_cursor_to_saved_position(t_input_context *state);
size_t	cursor_get_column(t_input_context *state, size_t index);
size_t	cursor_get_row(t_input_context *state, size_t index);

#endif
