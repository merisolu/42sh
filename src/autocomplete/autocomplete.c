/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:07:51 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/12 12:58:02 by amann            ###   ########.fr       */
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
		if (c == '/' || c == '.' || c == ' ')
			res = SEARCH_FILE_PATH;
		else if (c == '$' && (i == 0 || trimmed_input[i - 1] == ' '))
			res = SEARCH_VARIABLE;
		i++;
	}
	return (res);
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

/*
 * Here we are searching for an absolute path if the query begins with a '/',
 * in other cases a relative path.
 */

static char	*find_query(char *str)
{
	size_t	len;
	size_t	start;

	len = ft_strlen(str);
	start = 0;
	while (len)
	{
		if (str[len] == ' ')
			start = len + 1;
		len--;
	}
	return (ft_strdup(str + start));
}

static size_t	last_slash(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (len)
	{
		if (str[len] == '/')
			break ;
		len--;
	}
	return (len + 1);
}

char	**search_file_paths(char *trimmed_input, bool second_tab)
{
	char	**search_result;
	char	*query;
	int		count;
	char	*path;
	t_auto	autocomp;

	search_result = (char **) ft_memalloc(sizeof(char *) * 200);
	if (!search_result)
		print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
	count = 0;
	query = find_query(trimmed_input);
	initialise_autocomp(&autocomp, &query, &search_result, &count);
	if (query[0] == '/')
	{
		path = ft_strndup(query, last_slash(query));
		char *temp = ft_strdup(ft_strrchr(query, '/') + 1);
		ft_strdel(&query);
		query = temp;
	}
	else
		path = ft_strdup(".");
	//ft_printf("\npath = %s | query = %s\n", path, query);
	autocomp.query_len = ft_strlen(query);
	search_path(path, &autocomp, false);
	if (count > 1 && !second_tab) // more enhanced check needed here
	{
		ft_free_null_array((void **)search_result);
		return (NULL);
	}
	return (search_result);
}

//edge case, if the query begins with '.' this will always expand to './' (test this!)
//if the query begins './' we should search for executables in the current dir

//if there are multiple possible proposals, but they all start with the same next letter
//or two, autocomplete will print those next letters. eg:
//
//$M will autocomplete to $MA on first tab press. Then 2 tab presses more suggest 3 poss
//options, all starting with $MA.

int	autocomplete(t_state *state, bool second_tab)
{
	char			*trimmed_input;
	char			**search_result;
	t_search_type	search_type;
	t_input_context	ic;

	ic = state->input_context;
	if (!state || ft_strlen(ic.input) == 0)
		return (0);
	trimmed_input = trim_input_to_cursor(ic);
	if (!trimmed_input)
		return (0);
	search_type = get_search_type(trimmed_input);
	//ft_printf("\n-- *%s* cursor idx = %zu\n", trimmed_input, ic.cursor);
	search_result = NULL;

	if (search_type == SEARCH_COMMAND) //first word, not a path, search commands/builtins
		search_result = search_commands(state, trimmed_input, second_tab);
	else if (search_type == SEARCH_FILE_PATH) //search file paths
		search_result = search_file_paths(trimmed_input, second_tab);
	else if (search_type == SEARCH_VARIABLE) //search variables
		search_result = NULL;

	ft_strdel(&trimmed_input);

	if (!search_result)
		return (0);
	//nb, results should be sorted alphabetically, duplicates removed and printed in columns
	ft_putendl("");
	for (int i = 0; search_result[i]; i++)
		ft_printf("%s\n", search_result[i]);

	save_cursor(&(state->input_context));

	/*
	if (temp) //copies the found string over the input, will need to be refactored to handle inserting strings...
	{
		ft_strcpy(state->input_context.input, temp);
		state->input_context.cursor = ft_strlen(state->input_context.input);
		free(temp);
	}*/
	ft_free_null_array((void **) search_result);
	free(trimmed_input);
	return (0);
}
