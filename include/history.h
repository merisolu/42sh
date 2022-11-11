/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:14:31 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/11 16:18:16 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

/* Includes */

# include "libft.h"
# include "general.h"

/* Files */

/* history.c */
int				history_store(char *input, t_state *state, int into_temp);
int				history_recall(int diff, t_state *state);

#endif