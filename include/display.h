/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:28:46 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 15:34:13 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

/* Includes */

# include <termcap.h>

# include "libft.h"
# include "general.h"
# include "input.h"
# include "utils.h"
# include "cursor.h"

/* Files */

/* display.c */
void	display(t_input_context *context, int force);

#endif
