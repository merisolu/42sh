/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:37:40 by amann             #+#    #+#             */
/*   Updated: 2023/01/12 19:51:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

t_auto	autocomp_setup(char **query, bool brackets, char ***search_result)
{
	t_auto	autocomp;
	int		count;

	count = ft_null_array_len((void **)*search_result);
	autocomp.count = &count;
	autocomp.query = query;
	autocomp.query_len = ft_strlen(*query);
	autocomp.search_results = search_result;
	autocomp.query_len += 1;
	if (brackets)
		autocomp.query_len += 1;
	return (autocomp);
}

char	**search_variables(t_state *state, char **ti, bool second_tab)
{
	char	**search_result;
	char	*dollar_start;
	char	*query;
	bool	brackets;

	(void) second_tab;
	search_result = (char **) ft_memalloc(sizeof(char *) * INPUT_MAX_SIZE);
	if (!search_result)
		return (print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	dollar_start = ft_strchr(*ti, '$');
	brackets = *(dollar_start + 1) == '{';
	query = dollar_start + 1;
	if (brackets)
		query = dollar_start + 2;
	if (!search_env_intern(state->env, query, &search_result, brackets)
		|| !search_env_intern(state->intern, query, &search_result, brackets))
	{
		ft_free_null_array((void **)search_result);
		return (NULL);
	}
	return (wrap_up(autocomp_setup(&query, brackets, &search_result),
			second_tab));
}
