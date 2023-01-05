/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:37:24 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/05 13:43:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include "utils.h"
# include "signals.h"

/* setup.c */
int	setup(char *const **env, t_state *state);

/* setup_fd.c */
int	setup_fd(void);

/* setup_input.c */
int	setup_input(t_state *state);

/* setup_termcaps.c */
int	setup_termcaps(void);

#endif
