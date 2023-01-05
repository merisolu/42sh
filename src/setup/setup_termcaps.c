/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_termcaps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:31:17 by amann             #+#    #+#             */
/*   Updated: 2023/01/05 14:44:49 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

bool	setup_termcaps(void)
{
	char	*term;
	int		database_result;

	term = getenv("TERM");
	if (!term)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
				ERR_ENV_MISSING_TERM));
	database_result = tgetent(NULL, term);
	if (database_result < 0)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
				ERR_TERMCAP_NO_ACCESS));
	else if (database_result == 0)
		return (print_error_bool(false, ERRTEMPLATE_SIMPLE,
				ERR_TERMCAP_NO_ENTRY));
	return (true);
}
