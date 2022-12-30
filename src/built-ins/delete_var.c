/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:14:26 by amann             #+#    #+#             */
/*   Updated: 2022/12/30 16:14:46 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

bool	exported_no_equals(char *name, t_state *state)
{
	int	i;

	i = 0;
	while ((state->exported)[i])
	{
		if (ft_strequ(name, (state->exported)[i]))
			return (true);
		i++;
	}
	return (false);
}

void	delete_var(char *name, t_state *state)
{
	int		i;
	char	**temp;

	i = 0;
	while ((state->exported)[i])
	{
		if (ft_strequ(name, (state->exported)[i]))
		{
			ft_strdel((char **)&((state->exported)[i]));
			while ((state->exported)[i + 1])
			{
				temp = (char **)&((state->exported)[i]);
				*temp = (char *)((state->exported)[i + 1]);
				i++;
			}
			temp = (char **)&((state->exported)[i]);
			*temp = NULL;
			break ;
		}
		i++;
	}
	return ;
}
