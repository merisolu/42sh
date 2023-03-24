/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:37:40 by amann             #+#    #+#             */
/*   Updated: 2023/03/24 17:48:06 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static bool c_b(char *dollar_start)
{
	return (*(dollar_start + 1) == '{');
}

void search_variables(t_auto *autocomp, t_state *state)
{
	char *dollar;
	char *temp;

	autocomp->search_result = (char **)ft_memalloc(sizeof(char *) * INPUT_MAX_SIZE);
	if (!(autocomp->search_result))
	{
		print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL);
		return;
	}
	temp = find_query(autocomp->trimmed_input, ' ', state, false);
	dollar = ft_strchr(temp, '$');
	if (c_b(dollar))
		autocomp->query = ft_strdup(dollar + 2);
	else
		autocomp->query = ft_strdup(dollar + 1);
	autocomp->query_len = ft_strlen(autocomp->query) + c_b(dollar);
	search_env_intern(state->env, autocomp, c_b(dollar));
	search_env_intern(state->intern, autocomp, c_b(dollar));
	free(temp);
	return;
}
