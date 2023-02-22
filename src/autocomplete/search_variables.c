/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:37:40 by amann             #+#    #+#             */
/*   Updated: 2023/02/22 13:22:08 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static t_auto	autocomp_setup(char **query, bool brackets, char ***sr)
{
	t_auto	autocomp;

	autocomp.count = NULL;
	autocomp.query = query;
	autocomp.query_len = ft_strlen(*query);
	autocomp.search_results = sr;
	autocomp.query_len += 1;
	if (brackets)
		autocomp.query_len += 1;
	return (autocomp);
}

static bool	c_b(char *dollar_start)
{
	return (*(dollar_start + 1) == '{');
}

char	**search_variables(t_state *s, char **ti, t_auto_bools *a_bools)
{
	char	**search_result;
	char	*dollar;
	char	*query;
	char	*temp;
	t_auto	autocomp;

	search_result = (char **) ft_memalloc(sizeof(char *) * INPUT_MAX_SIZE);
	if (!search_result || !ti)
		return (print_error_ptr(NULL, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	temp = find_query(*ti, ' ', s, false);
	dollar = ft_strchr(temp, '$');
	if (c_b(dollar))
		query = ft_strdup(dollar + 2);
	else
		query = ft_strdup(dollar + 1);
	if (!search_env_intern(s->env, query, &search_result, c_b(dollar))
		|| !search_env_intern(s->intern, query, &search_result, c_b(dollar)))
	{
		free(temp);
		ft_free_null_array((void **)search_result);
		return (NULL);
	}
	free(temp);
	autocomp = autocomp_setup(&query, c_b(dollar), &search_result);
	return (wrap_up(&autocomp, a_bools));
}
