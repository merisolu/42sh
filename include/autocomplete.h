/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:08:42 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/11 15:27:40 by amann            ###   ########.fr       */
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

typedef struct	s_auto
{
	int		*count;
	char	**query;
	char	***search_results;
}			t_auto;

/* Files */

/* autocomplete.c */
int		autocomplete(t_state *state, bool tab);
void	initialise_autocomp(t_auto *autocomp, char **query, char ***search_result, int *count);

/* search_commands.c */
char	**search_commands(t_state *state, char *trimmed_input, bool second_tab);

/* search_path.c */
int		search_path(char *path, t_auto *autocomp, bool bin);

#endif
