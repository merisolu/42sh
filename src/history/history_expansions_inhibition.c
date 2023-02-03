/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions_inhibition.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:02:50 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/03 13:40:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static bool	is_quote_inhibited_at_index(char *input, int end)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (i < end)
	{
		if (quote == '\0' && (input[i] == '\'' || input[i] == '"'))
			quote = input[i];
		else if (input[i] == quote)
			quote = '\0';
		i++;
	}
	return (quote == '\'');
}

bool	is_history_expansion_inhibited(char *input, int index)
{
	if (index == 0)
		return (false);
	if (input[index - 1] == '\\')
		return (true);
	return (is_quote_inhibited_at_index(input, index));
}
