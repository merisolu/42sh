/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:22:23 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/08 13:14:26 by jumanner         ###   ########.fr       */
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
int	apply_terminal_config(struct termios *config);
int	configure_terminal(struct termios *input, struct termios *original);

#endif
