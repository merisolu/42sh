/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:14:26 by amann             #+#    #+#             */
/*   Updated: 2023/02/14 15:57:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

bool	exported_no_equals(char *name, t_state *state)
{
	int	i;

	i = 0;
	while (state->exported && (state->exported)[i])
	{
		if (ft_strequ(name, (state->exported)[i]))
			return (true);
		i++;
	}
	return (false);
}

static void	shuffle_down(char *const **arr, int i)
{
	char	**temp;

	while ((*arr)[i + 1])
	{
		temp = (char **)&((*arr)[i]);
		*temp = (char *)((*arr)[i + 1]);
		i++;
	}
	temp = (char **)&((*arr)[i]);
	*temp = NULL;
}

static size_t	get_name_len(char *name)
{
	size_t	name_len;

	if (ft_strchr(name, '='))
	{
		name_len = 0;
		while (name[name_len] && name[name_len] != '=')
			name_len++;
	}
	else
		name_len = ft_strlen(name);
	return (name_len);
}

void	delete_var(char *name, char *const **arr)
{
	int		i;
	size_t	name_len;
	size_t	var_len;

	if (!name || !arr || !*arr)
		return ;
	name_len = get_name_len(name);
	i = 0;
	while ((*arr)[i])
	{
		var_len = valid_env_name_length((*arr)[i]);
		if (var_len == name_len
			&& ft_strnequ(name, (*arr)[i], var_len))
		{
			free((*arr)[i]);
			shuffle_down(arr, i);
			break ;
		}
		i++;
	}
	return ;
}
