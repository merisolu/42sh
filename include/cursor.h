/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:43:34 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/20 15:28:29 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURSOR_H
# define CURSOR_H

/* Includes */

# include <termcap.h>

# include "input.h"

/* Files */

/* cursor.c */
int		parse_cursor(char *buffer, t_input_context *context);
void	save_cursor(t_input_context *context);
void	load_cursor(t_input_context *context);

/* cursor_utils.c */
void	move_cursor_to_saved_position(t_input_context *context);
size_t	cursor_get_column(t_input_context *context, size_t index);
size_t	cursor_get_row(t_input_context *v, size_t index);

#endif
