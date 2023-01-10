/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:07:51 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/10 13:58:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static int	check_execution_rights(char *path, char *name)
{
	int		result;
	char	*temp;

	ft_path_join(path, name, &temp);
	if (!temp)
		return (-1);
	result = (access(temp, X_OK) == 0);
	free(temp);
	return (result);
}

static int	check_match_is_file(char *path, char *name)
{
	int		result;
	char	*temp;

	ft_path_join(path, name, &temp);
	if (!temp)
		return (-1);
	result = (ft_is_file(temp) || ft_points_to_file(temp));
	free(temp);
	return (result);
}

/*
 * Searches the specific path for an executable file with a name matching
 * partial_name. The resulting file name will be put in *result. *result will
 * need to be freed once it's not used. It will be NULL if no match is found,
 * or on error.
 */

static int	search_path(char *path, char *partial_name, char **result)
{
	DIR				*dir;
	struct dirent	*entry;

	*result = NULL;
	dir = opendir(path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strnequ(partial_name, entry->d_name, ft_strlen(partial_name))
			&& check_execution_rights(path, entry->d_name) == 1
			&& check_match_is_file(path, entry->d_name) == 1)
		{
			*result = ft_strdup(entry->d_name);
			closedir(dir);
			if (!(*result))
				return (-1);
			return (1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

/*
 * Searches for a binary that at least partially matches the given input and is
 * located in any of the folders listed in the PATH environment variable.
 *
 * *result will be NULL if no match was found, or if an error has occured.
 */

static void	search_from_paths(char *const *env, char *input, char **result)
{
	int		search_return_value;
	char	**paths;
	size_t	i;

	if (!result)
		return ;
	paths = ft_strsplit(env_get("PATH", env), ':');
	if (!paths)
	{
		print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
		return ;
	}
	i = 0;
	search_return_value = 0;
	while (paths[i] && search_return_value == 0)
	{
		search_return_value = search_path(paths[i], input, result);
		if (search_return_value == -1)
		{
			print_error(-1, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
			break ;
		}
		i++;
	}
	ft_free_null_array((void **)paths);
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

	input_to_cursor = ft_strndup(ic.input, ic.cursor);
	if (!input_to_cursor)
		return (print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	int i = 0;
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
	//determine where we are searching based on the cursor context
	//if we are in the first word, and there is no / char, we are only
	//searching for built-ins and commands.

static int	get_search_type(char *trimmed_input)
{
	int		i;
	bool	first_word;
	bool	file_path;
	bool	variable;
	char	c;

	first_word = true;
	file_path = false;
	variable = false;
	i = 0;
	while (trimmed_input[i])
	{
		c = trimmed_input[i];
		if (c == '/' || c == '.')
		{
			file_path = true;
			variable = false;
		}
		else if (c == ' ')
		{
			first_word = false;
			file_path = true;
			variable = false;
		}
		else if (c == '$' &&  (i == 0 || trimmed_input[i - 1] == ' '))
		{
			variable = true;
			file_path = false;
		}
		i++;
	}


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

int	autocomplete(t_state *state, bool tab)
{
	char	*trimmed_input;
	char	*temp;
	int		search_type;
	t_input_context ic;

	(void)tab;
	ic = state->input_context;
	if (!state || ft_strlen(ic.input) == 0)
		return (0);
	trimmed_input = trim_input_to_cursor(ic);
	if (!trimmed_input)
		return (0);
	search_type = get_search_type(trimmed_input);


	ft_printf("\n-- *%s* cursor idx = %zu\n", trimmed_input, ic.cursor);
	ft_printf("\nfirst word = %d | file_path =  %d | variable = %d\n", first_word, file_path, variable);
	temp = built_in_search(trimmed_input);
	if (!temp)
		search_from_paths(state->env, trimmed_input, &temp);
	if (temp)
	{
		ft_strcpy(state->input_context.input, temp);
		state->input_context.cursor = ft_strlen(state->input_context.input);
		free(temp);
	}
	free(trimmed_input);
	return (0);
}
