/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:18 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/20 13:00:00 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* Includes */

# if __linux__
#  include <signal.h>
# endif

# include "libft.h"
# include "general.h"
# include "display.h"

/* Files */

/* signal.c */
void	check_signal(t_state *state);

/* signal_handlers.c */
void	set_signal_handling(void);
void	reset_signal_handlers(void);

#endif
