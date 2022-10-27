/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:22:23 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 15:22:59 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

/* Includes */

# include <termcap.h>

# include "libft.h"
# include "general.h"

/* Constants */

# define CC_SUSPEND VDSUSP

# if __linux__
#  undef CC_SUSPEND
#  define CC_SUSPEND VSUSP
# endif

/* Files */

/* terminal_configuration.c */
int				configure_terminal(t_state *state);
int				set_input_config(t_state *state);
int				set_orig_config(t_state *state);

#endif
