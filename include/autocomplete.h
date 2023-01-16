/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:08:42 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/16 14:01:22 by amann            ###   ########.fr       */
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

typedef struct s_auto
{
	int		*count;
	char	**query;
	size_t	query_len;
	char	***search_results;
}			t_auto;

/* Files */

/* autocomplete.c */
int		autocomplete(t_state *state, bool second_tab);
void	initialise_autocomp(t_auto *autocomp, char **query, \
		char ***search_result, int *count);

/* check_result_is_dir.c */
bool	check_result_is_dir(char *path, t_auto *autocomp, \
		struct dirent *entry, DIR *dir);

/* find_query. */
char	*find_query(char *str, char c);

size_t	last_slash(char *str);

/* search_commands.c */
char	**search_commands(t_state *state, char **trimmed_input, \
		bool second_tab);

/* search_exec.c */
char	**search_exec(char ***sr, char **ti, bool second_tab);
char	**check_exec(char ***sr, t_auto autocomp, char **ti, bool second_tab);

/* search_file_paths.c */
char	**search_file_paths(char **trimmed_input, bool second_tab);

/* search_variables.c */
char	**search_variables(t_state *state, char **ti, bool second_tab);

/* search_env_intern.c */
bool	search_env_intern(char *const *arr, char *query, char ***sr, bool b);

/* directory_search.c */
int		directory_search(char *path, t_auto *autocomp, bool bin, bool exec);

/* directory_search_loops.c */
int		exec_search(char *path, t_auto *ac, struct dirent *entry, DIR *dir);
int		bin_search(char *path, t_auto *ac, struct dirent *entry, DIR *dir);
int		fp_search(char *path, t_auto *ac, struct dirent *entry, DIR *dir);

/* filter_matching.c */
bool	filter_matching(t_auto autocomp);

/* truncate_result.c */
void	truncate_result(t_auto autocomp);

/* wrap_up.c */
char	**wrap_up(t_auto autocomp, bool second_tab);
#endif
