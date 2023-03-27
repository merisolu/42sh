/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_file_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:44:44 by amann             #+#    #+#             */
/*   Updated: 2023/03/27 16:27:09 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

size_t	last_slash(char *str)
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

static void	reset_query_and_path(t_auto *autocomp, char **path)
{
	char	*temp;

	if (ft_strchr(autocomp->query, '/'))
	{
		*path = ft_strndup(autocomp->query, last_slash(autocomp->query));
		temp = ft_strdup(ft_strrchr(autocomp->query, '/') + 1);
		free(autocomp->query);
		autocomp->query = temp;
		return ;
	}
	temp = getcwd(NULL, PATH_MAX);
	*path = ft_strjoin(temp, "/");
	free(temp);
	return ;
}

static bool	set_exec(char *path, char *ti)
{
	bool	first_word;
	int		i;

	first_word = true;
	i = (int)ft_strlen(path) - 1;
	while (i >= 0)
	{
		if (ti[i] == ' ')
		{
			first_word = false;
			break ;
		}
		i--;
	}
	if (first_word && path[0] == '.')
		return (true);
	return (false);
}

void	search_file_paths(t_auto *autocomp, t_state *state)
{
	char	*path;

	autocomp->search_result = (char **)ft_memalloc(
			sizeof(char *) * INPUT_MAX_SIZE
			);
	if (!autocomp->search_result)
	{
		print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
		return ;
	}
	autocomp->query = find_query(autocomp->trimmed_input, ' ', state, true);
	path = NULL;
	reset_query_and_path(autocomp, &path);
	if (!path || !(autocomp->query))
	{
		print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
		return ;
	}
	autocomp->query_len = ft_strlen(autocomp->query);
	directory_search(
		path, autocomp, false, set_exec(path, autocomp->trimmed_input)
		);
	free(path);
	return ;
}
