/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:08:42 by jumanner          #+#    #+#             */
/*   Updated: 2023/03/26 16:24:48 by amann            ###   ########.fr       */
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
# include "signals.h"
# include "expansion.h"

/* Constants */

# define AUTOCOMP_DISPLAY_LIMIT 100

/* Structs and enums */

typedef enum e_search_type
{
	SEARCH_COMMAND,
	SEARCH_FILE_PATH,
	SEARCH_VARIABLE
}	t_search_type;

typedef struct s_auto_bools
{
	bool	filtered;
	bool	second_tab;
}			t_auto_bools;

typedef struct s_auto
{
	char			*trimmed_input;
	t_search_type	search_type;
	char			**search_result;
	int				count;
	char			*query;
	size_t			query_len;
	t_auto_bools	auto_bools;
}			t_auto;

typedef struct s_autocomplete_display
{
	size_t	max_len;
	size_t	col_width;
	size_t	col_height;
	size_t	total_cols;
	size_t	start_y;
	size_t	start_x;
	size_t	current_col;
	size_t	i;
	size_t	row_counter;
	size_t	offset;
}			t_autocomplete_display;

/* Files */

/* autocomplete.c */
int		autocomplete(t_state *state, bool second_tab);

/* autocomplete_display_control.c */
int		autocomplete_display_control(t_auto *autocomp, t_state *state);

/* autocomplete_display_columns.c */
void	autocomplete_display_columns(char **search_result, size_t len, \
		t_state *state);

/* autocomplete_handle_dot.c */
int		autocomplete_handle_dot(t_state *state, char *ti);

/* autocomplete_position_cursor.c */
void	cursor_to_end(t_input_context *ic, size_t *orig_cursor);
void	cursor_to_orig(t_input_context *ic, size_t orig_cursor);

/* check_result_is_dir.c */
bool	check_result_is_dir(char *path, t_auto *autocomp, \
		struct dirent *entry, DIR *dir);

/* filter_matching.c */
bool	filter_matching(t_auto *autocomp);

/* find_longest.c */
size_t	find_longest(char **search_results);

/* find_query.c */
char	*find_query(char *str, char c, t_state *state, bool expand);

/* insert_expansion.c */
void	insert_expansion(t_input_context *ctx, char *exp);

/* search_commands.c */
void	search_commands(t_auto *autocomp, t_state *state);

/* search_file_paths.c */
void	search_file_paths(t_auto *autocomp, t_state *state);
size_t	last_slash(char *str);

/* search_variables.c */
void	search_variables(t_auto *autocomp, t_state *state);

/* search_env_intern.c */
bool	search_env_intern(char *const *arr, t_auto *autocomp, bool b);

/* directory_search.c */
int		directory_search(char *path, t_auto *autocomp, bool bin, bool exec);

/* directory_search_loops.c */
int		exec_search(char *path, t_auto *ac, struct dirent *entry, DIR *dir);
int		bin_search(char *path, t_auto *ac, struct dirent *entry, DIR *dir);
int		fp_search(char *path, t_auto *ac, struct dirent *entry, DIR *dir);

/* truncate_result.c */
void	truncate_result(t_auto *autocomp);

/* wrap_up.c */
void	wrap_up(t_auto *autocomp);
#endif
