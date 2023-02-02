/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:14:31 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/02 14:39:08 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

/* Includes */

# include <fcntl.h>

# include "general.h"
# include "utils.h"

/* Constants */

# define HISTORY_FILE ".42sh_history"

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

/* history_search.c */
bool	history_search(t_state *state);

/* history_input.c */
bool	check_history_reserved_sequences(t_state *state);

/* history_expansions.c */
int		history_expand(t_state *state);

/* history_utils.c */
int		history_seek(t_state *state, int start, char *look_for,
			bool anywhere);
int		history_number_to_index(int num, t_state *state);
int		get_history_length(t_state *state);
char	*get_history_file_path(void);

#endif