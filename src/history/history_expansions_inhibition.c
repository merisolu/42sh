/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions_inhibition.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:02:50 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/03 12:34:13 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

bool	is_history_expansion_inhibited(char *input, int index)
{
	if (index == 0)
		return (false);
	if (input[index - 1] == '\\')
		return (true);
	return (false);
}
