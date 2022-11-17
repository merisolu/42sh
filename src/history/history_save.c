/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:45:48 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/17 11:27:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static char	*get_file_path(void)
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
	ft_path_join(home_dir, ".21sh_history", &result);
	free(home_dir);
	return (result);
}

void	history_save(t_state *state)
{
	int		file;
	char	*path;
	int		i;

	path = get_file_path();
	if (!path)
		return ;
	file = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (file == -1)
	{
		free(path);
		return ;
	}
	i = HISTORY_SIZE - 1;
	while (ft_strlen(state->history[i]) == 0 && i > 1)
		i--;
	while (i > 0)
	{
		write(file, state->history[i], ft_strlen(state->history[i]));
		write(file, "\n", 1);
		i--;
	}
	close(file);
	free(path);
}
