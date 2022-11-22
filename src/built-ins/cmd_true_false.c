/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_true.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:50:29 by amann             #+#    #+#             */
/*   Updated: 2022/11/22 14:00:57 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int		cmd_true(char *const *args, t_state *state)
{
	(void)args;
	(void)state;
	return (0);
}

int		cmd_false(char *const *args, t_state *state)
{
	(void)args;
	(void)state;
	return (1);
}
