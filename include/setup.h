/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:37:24 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/05 15:21:04 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include "utils.h"
# include "hash.h"
# include "signals.h"

/* setup.c */
bool	setup(char *const **env, t_state *state, bool stdin);

/* setup_fd.c */
bool	setup_fd(void);

/* setup_input.c */
bool	setup_input(t_state *state);

/* setup_termcaps.c */
bool	setup_termcaps(void);

#endif
