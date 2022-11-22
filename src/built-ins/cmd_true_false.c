/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_true_false.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:50:29 by amann             #+#    #+#             */
/*   Updated: 2022/11/22 16:20:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*
 * In the shell, 0 is true (i.e. the program executed successfully)
 * and 1 (or any other positive integer) is false (i.e. something went wrong)
 */

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
