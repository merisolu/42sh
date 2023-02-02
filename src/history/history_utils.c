/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:39:01 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/02 13:04:58 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int	history_number_to_index(int num, t_state *state)
{
	return (get_history_length(state) - num + 1);
}

int	get_history_length(t_state *state)
{
	int	i;

	i = 1;
	while (i < HISTORY_SIZE && state->history[i][0] != '\0')
		i++;
	return (i - 1);
}

char	*get_history_file_path(void)
{
	char			*result;
	char			*home_dir;
	struct passwd	*pw;

	pw = getpwuid(getuid());
	if (!pw)
		return (NULL);
	home_dir = ft_strdup(pw->pw_dir);
	if (!home_dir)
		return (NULL);
	ft_path_join(home_dir, HISTORY_FILE, &result);
	free(home_dir);
	return (result);
}
