/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:14:26 by amann             #+#    #+#             */
/*   Updated: 2023/01/02 16:03:30 by amann            ###   ########.fr       */
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

void	delete_var(char *name, char *const **arr)
{
	int		i;
	char	**temp;

	i = 0;
	while ((*arr)[i])
	{
		//if (ft_strchr((*arr)[i], '='))

		if (ft_strequ(name, (*arr)[i]))
		{
			free((*arr)[i]);
			while ((*arr)[i + 1])
			{
				temp = (char **)&((*arr)[i]);
				*temp = (char *)((*arr)[i + 1]);
				i++;
			}
			temp = (char **)&((*arr)[i]);
			*temp = NULL;
			break ;
		}
		i++;
	}
	return ;
}
