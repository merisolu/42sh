/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:36:20 by amann             #+#    #+#             */
/*   Updated: 2023/01/05 14:42:18 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

bool	setup_fd(void)
{
	int		ret1;
	int		ret2;

	ret1 = 0;
	ret2 = 0;
	if (!isatty(1))
		ret1 = open(ttyname(ttyslot()), O_RDWR);
	if (!isatty(2))
		ret2 = open(ttyname(ttyslot()), O_RDWR);
	if (ret1 == -1 || ret2 == -1)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE, ERR_OPEN_FAIL));
	return (true);
}
