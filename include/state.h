/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:28:46 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 14:47:11 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

/* Includes */

# include <termcap.h>

# include "libft.h"
# include "general.h"
# include "utils.h"
# include "cursor.h"

/* Files */

/* state.c */
void	print_state(t_state *state);

#endif
