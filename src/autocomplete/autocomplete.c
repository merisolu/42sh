/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:07:51 by jumanner          #+#    #+#             */
/*   Updated: 2023/03/23 13:05:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

void	initialise_autocomp(t_auto *autocomp, char **query, \
		char ***search_result, int *count)
{
	autocomp->query = query;
	autocomp->search_results = search_result;
	autocomp->count = *count;
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
		if (c == ' ' || c == '/')
			res = SEARCH_FILE_PATH;
		else if (c == '$' && (i == 0 || trimmed_input[i - 1] == ' '))
			res = SEARCH_VARIABLE;
		i++;
	}
	return (res);
}

//if an autocommpletion happens, tab should be reset.
//This can be controlled by the return value

static int	free_and_display(char **ti, t_state *state, char ***sr, bool f)
{
	int	ret;

	ft_strdel(ti);
	if (!*sr)
		return (0);
	ret = autocomplete_display_control(state, sr, f);
	ft_free_null_array((void **) *sr);
	return (ret);
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

int	autocomplete(t_state *state, bool second_tab)
{
	t_auto			autocomp;

	if (!state)
		return (0);
	ft_bzero((void *)&autocomp, sizeof(autocomp));
	autocomp.trimmed_input = trim_input_to_cursor(state->input_context);
	if (!autocomp.trimmed_input)
		return (0);
	if (ft_strequ(autocomp.trimmed_input, "."))
		return (autocomplete_handle_dot(state, autocomp.trimmed_input));
	autocomp.search_type = get_search_type(autocomp.trimmed_input);
	autocomp.auto_bools.filtered = false;
	autocomp.auto_bools.second_tab = second_tab;
	autocomp.search_result_final = NULL;
	if (autocomp.search_type == SEARCH_COMMAND)
		autocomp.search_result_final = search_commands(state, &autocomp);
	else
		return (0);
	/*else if (autocomp.search_type == SEARCH_FILE_PATH)
		autocomp.search_result_final = search_file_paths(&(autocomp.trimmed_input), &(autocomp.auto_bools), state);
	else if (autocomp.search_type == SEARCH_VARIABLE)
		autocomp.search_result_final = search_variables(state, &(autocomp.trimmed_input), &(autocomp.auto_bools));*/
	return (free_and_display(&(autocomp.trimmed_input), state, &(autocomp.search_result_final),
			autocomp.auto_bools.filtered));
}
