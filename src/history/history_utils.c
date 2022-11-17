/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:39:01 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/17 11:39:27 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

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
