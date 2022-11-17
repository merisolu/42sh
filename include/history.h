/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:14:31 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/17 11:04:19 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

/* Includes */

# include <pwd.h>
# include <fcntl.h>

# include "libft.h"
# include "general.h"

/* Files */

/* history.c */
int		history_store(char *input, t_state *state, int into_temp);
int		history_recall(int diff, t_state *state);

/* history_save.c */
void	history_save(t_state *state);

#endif