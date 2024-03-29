/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:18 by jumanner          #+#    #+#             */
/*   Updated: 2023/03/23 12:11:51 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* Includes */

# if __linux__
#  include <signal.h>
#  define SIGEMT SIGBUS
# endif

# include "libft.h"
# include "general.h"
# include "display.h"

/* Types */

typedef struct s_signal_name_dispatch
{
	int		signal;
	char	*name;
}	t_signal_name_dispatch;

/* Files */

/* signal.c */
void	check_signal(t_state *state);

/* signal_handlers.c */
void	set_signal_handling(void);
void	reset_signal_handlers(void);

/* signal_print.c */
void	print_signal(int signal);

#endif
