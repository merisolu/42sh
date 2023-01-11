/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:08:42 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/11 14:24:16 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

/* Includes */

# include <dirent.h>

# include "libft.h"
# include "general.h"
# include "built_ins.h"
# include "cursor.h"

/* Structs and enums */

typedef enum e_search_type
{
	SEARCH_COMMAND,
	SEARCH_FILE_PATH,
	SEARCH_VARIABLE
}	t_search_type;

/* Files */

/* autocomplete.c */
int		autocomplete(t_state *state, bool tab);

/* search_commands.c */
char	**search_commands(t_state *state, char *trimmed_input, bool second_tab);

/* search_path.c */
int		search_path(char *path, char *partial_name, char ***search_results, int *count);

#endif
