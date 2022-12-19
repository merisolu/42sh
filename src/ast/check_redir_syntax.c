/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:02:10 by amann             #+#    #+#             */
/*   Updated: 2022/12/16 16:10:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	check_redir_syntax(t_token *cursor)
{
	if (cursor->type == TOKEN_GT)
	{
		if (!ft_strequ(cursor->value, ">") && !ft_strequ(cursor->value, ">>")
			&& !ft_strequ(cursor->value, FD_AGG_OUT))
			return (print_bool_sep_error(ERR_SYNTAX, cursor, false));
	}
	else if (cursor->type == TOKEN_LT)
	{
		if (!ft_strequ(cursor->value, "<") && !ft_strequ(cursor->value, "<<"))
			return (print_bool_sep_error(ERR_SYNTAX, cursor, false));
	}
	if (!(cursor->next)
		|| !(cursor->next->type & (TOKEN_WORD | TOKEN_WHITESPACE)))
		return (print_bool_syntax_error(ERR_SYNTAX, cursor, false));
	if (cursor->next->type == TOKEN_WORD
		&& ast_fd_agg_format_check(&(cursor->next)))
		return (print_bool_syntax_error(ERR_SYNTAX, cursor, false));
	if (cursor->next->type == TOKEN_WHITESPACE
		&& (!(cursor->next->next) || cursor->next->next->type != TOKEN_WORD
			|| ast_fd_agg_format_check(&(cursor->next->next))))
		return (print_bool_syntax_error(ERR_SYNTAX, cursor->next, false));
	return (true);
}
