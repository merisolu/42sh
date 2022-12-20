/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:14:31 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/20 15:28:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

/* Includes */

# include <fcntl.h>

# include "general.h"
# include "utils.h"

/* Constants */

# define HISTORY_FILE ".21sh_history"

/* Errors */

# define ERR_CANNOT_OPEN_HISTORY "Unable to recover history from file."

/* Files */

/* history.c */
void	history_store(char *input, t_state *state, int into_temp);
void	history_recall(int diff, t_state *state);

/* history_save.c */
void	history_save(t_state *state);

/* history_load.c */
void	history_load(t_state *state);

/* history_utils.c */
char	*get_history_file_path(void);

#endif