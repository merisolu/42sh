/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:22:23 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/08 13:25:08 by jumanner         ###   ########.fr       */
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
int	terminal_apply_config(struct termios *config);
int	terminal_get_configs(struct termios *input, struct termios *original);

#endif
