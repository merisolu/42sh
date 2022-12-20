/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/20 15:28:02 by jumanner         ###   ########.fr       */
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
void	set_signal_handling(void);

#endif
