/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:07:51 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/16 18:56:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

void	initialise_autocomp(t_auto *autocomp, char **query, char ***search_result, int *count)
{
	autocomp->query = query;
	autocomp->search_results = search_result;
	autocomp->count = count;
}

/*
 * We need to base our search on the cursor position in the string and its
 * context. This function truncates the input up to the cursor and removes
 * any whitespace chars preceding the first word.
 */

static char	*trim_input_to_cursor(t_input_context ic)
{
	char	*input_to_cursor;
	char	*trimmed_input;
	int		i;

	if (ft_strlen(ic.input) == 0 || ic.cursor == 0)
		return (ft_strdup(""));
	input_to_cursor = ft_strndup(ic.input, ic.cursor);
	if (!input_to_cursor)
		return (print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	i = 0;
	while (input_to_cursor[i] == ' ')
		i++;
	trimmed_input = ft_strdup(input_to_cursor + i);
	free(input_to_cursor);
	if (ft_strlen(trimmed_input) == 0)
	{
		if (!trimmed_input)
			print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
		free(trimmed_input);
		return (NULL);
	}
	return (trimmed_input);
}

/*
 * This algo determines where we are searching based on the cursor context
 *
 * If we are in the first word, and there is no '/' or '.' char, we are only
 * searching for built-ins and commands.
 *
 * Once we hit the first whitespace char after the first word, we know we
 * are no longer looking for a builtin/command/bin.
 *
 * If we are in a word that begins with a '$' and does not contain '/' or '.'
 * then we know we are looking for a variable name.
 */

static t_search_type	get_search_type(char *trimmed_input)
{
	int		i;
	int		res;
	char	c;

	res = SEARCH_COMMAND;
	i = 0;
	while (trimmed_input[i])
	{
		c = trimmed_input[i];
		if (/*c == '/' || c == '.' ||*/ c == ' ')
			res = SEARCH_FILE_PATH;
		else if (c == '$' && (i == 0 || trimmed_input[i - 1] == ' '))
			res = SEARCH_VARIABLE;
		i++;
	}
	return (res);
}

bool	autocomplete_display_warning(t_state *state, size_t len)
{
	char	buffer[BUF_SIZE + 1];

	ft_bzero(&buffer, BUF_SIZE + 1);
	ft_dprintf(
			STDOUT_FILENO,
			"\nDisplay all %d possibilities? (y or n) ",
			len);
	while (1)
	{
		read(STDIN_FILENO, buffer, BUF_SIZE);
		if (ft_strchr(buffer, 'y'))
			break;
		if (ft_strchr(buffer, 'n') || g_last_signal == SIGINT)
		{
			ft_putendl("");
			if (g_last_signal == SIGINT)
				g_last_signal = 0;
			save_cursor(&(state->input_context));
			return (false);
		}
	}
	return (true);
}

void	free_and_reshuffle(char ***sr, int i)
{
	free((*sr)[i]);
	while ((*sr)[i])
	{
		(*sr)[i] = (*sr)[i + 1];
		i++;
	}
}
void	sort_options(char ***sr)
{
	int		i;
	int		res;
	char	*temp;
	bool	swapped;

	swapped = false;
	i = 0;
	while ((*sr)[i + 1])
	{
		res = ft_strcmp((*sr)[i], (*sr)[i + 1]);
		if (res == 0)
			free_and_reshuffle(sr, i);
		else if (res > 0)
		{
			temp = (*sr)[i];
			(*sr)[i] = (*sr)[i + 1];
			(*sr)[i + 1] = temp;
			swapped = true;
		}
		i++;
	}
	if (swapped)
		sort_options(sr);
}

/*
 * Provides contextual, dynamic, completion of:
 *		- commands
 *		- built-ins
 *		- files
 *		- internal and environment variables
 *
 * By contextual, we mean that depending on the cursor position and the input
 * state at the point tab is pressed, different completions will be proposed.
 *
 * For example, in the command "$> ls /", it the cursor is on the '/', only
 * directories and files from the root folder will be proposed. Furthermore,
 * if the command read 'l', rather than 'ls' and the cursor was over or next
 * to the 'l' when tab was pressed, only commands and/or builtins beginning
 * with 'l' would be proposed.
 *
 * In the command "$> echo ${S" only variables beginning with an 'S' will be
 * proposed.
 *
 * NB: if there is only one possible autocompletion that can be proposed,
 * this will be added to the input automatically. However, if there are
 * multiple, nothing happens, until tab is pressed again, and then all
 * possible propositions are printed to the STDOUT. The tab arg is a
 * static var from main that monitors this
 */


//edge case, if the query begins with '.' this will always expand to './' (test this!)
//if the query begins './' we should search for executables in the current dir

int	autocomplete(t_state *state, bool second_tab)
{
	char			*trimmed_input;
	char			**search_result;
	t_search_type	search_type;
	t_input_context	ic;

	ic = state->input_context;
	if (!state)// || ft_strlen(ic.input) == 0)
		return (0);
	trimmed_input = trim_input_to_cursor(ic);
	if (!trimmed_input)
		return (0);

	search_type = get_search_type(trimmed_input);
	//ft_printf("\n-- *%s* cursor idx = %zu\n", trimmed_input, ic.cursor);
	search_result = NULL;

	if (search_type == SEARCH_COMMAND) //first word, not a path, search commands/builtins
		search_result = search_commands(state, &trimmed_input, second_tab);
	else if (search_type == SEARCH_FILE_PATH) //search file paths
		search_result = search_file_paths(&trimmed_input, second_tab);
	else if (search_type == SEARCH_VARIABLE) //search variables
		search_result = search_variables(state, &trimmed_input, second_tab);

	ft_strdel(&trimmed_input);
	if (!search_result)
		return (0);
	//nb, results should be sorted alphabetically, duplicates removed and printed in columns
	//we also need to print a warning if we have a large number of potential results to print.
	//default min in bash is 100 (completion-query-items):
	//	https://www.gnu.org/software/bash/manual/bash.html#Readline-Init-File-Syntax
	size_t len = ft_null_array_len((void **)search_result);
	if (len == 1)
	{
		//ft_printf("\ninput: *%s* result: *%s* \n", ic.input, search_result[0]);
		//this should be based on cursor position rather than length
		ft_strcpy((state->input_context.input) + ft_strlen(ic.input), search_result[0]);
		state->input_context.cursor = ft_strlen(state->input_context.input);
		ft_free_null_array((void **) search_result);
		return (1);
	}
	else if (len)
	{
		sort_options(&search_result);
		len = ft_null_array_len((void **)search_result);
		if (len > 100 && !autocomplete_display_warning(state, len))
		{
			ft_free_null_array((void **) search_result);
			return (0);
		}
		//column display
		//maybe use load_cursor and a custom t_input_context struct to move the cursor to position.
		//update_window_size(ic) (utils.c) will add the window dimensions to the ic struct
		//NB results must be sorted in lexicographical order
		ft_putendl("");
		save_cursor(&(state->input_context));

		size_t	max_len;
		size_t	col_width;
		size_t	col_height;
		size_t	total_cols;
		size_t	start_y;
		size_t	start_x;
		size_t	current_col;

		max_len = find_longest(search_result);
		col_width = max_len + 2;
		total_cols = ic.width / col_width;
		if (total_cols == 0)
			total_cols = 1;
		col_height = (len / total_cols) + 1;
		if (len * col_width < ic.width)
			col_height = 1;

		start_x = ic.input_start_x - 1;
		start_y = ic.input_start_y;
		if (len > 100)
			start_y += 1;
//		ft_printf("total_cols = %zu | col_height = %zu | total options = %zu\n", total_cols, col_height, len);
		current_col = 0;
		size_t i = 0;
		size_t row_counter = 0;
		size_t offset = 0;
		while (search_result[i])
		{
			if (row_counter >= col_height)
			{
				row_counter = 0;
				if (current_col == 0 && offset)
					start_y -= offset + 2;
				current_col++;
			}
			ft_putstr(tgoto(tgetstr("cm", NULL),
					start_x + (current_col * col_width),
					start_y + row_counter));
			ft_printf("%s", search_result[i]);
			if (col_height > 1)
				ft_putendl("");
			if (start_y + row_counter > ic.height)
				offset++;
			i++;
			row_counter++;
		}
		if (start_y + col_height > ic.height)
			ft_putendl("");
		ft_putstr(tgoto(tgetstr("cm", NULL),
				start_x,
				start_y + col_height));

		save_cursor(&(state->input_context));
	}
	ft_free_null_array((void **) search_result);
	return (0);
}
