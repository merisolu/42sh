/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:02:10 by amann             #+#    #+#             */
/*   Updated: 2022/12/20 15:20:08 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	check_syntax_after_op(t_token *cursor)
{
	if (ast_fd_agg_format_check(&(cursor->next)))
		return (print_bool_syntax_error(ERR_SYNTAX, cursor, false));
	if (ft_isdigit_str(cursor->next->value) && cursor->next->next
		&& (cursor->next->next->type & (TOKEN_GT | TOKEN_LT)))
		return (print_bool_syntax_error(ERR_SYNTAX, cursor, false));
	return (true);
}

bool	check_redir_syntax(t_token *cursor)
{
	if (cursor->type == TOKEN_GT && (!ft_strequ(cursor->value, REDIR_OUT)
			&& !ft_strequ(cursor->value, REDIR_APPEND)
			&& !ft_strequ(cursor->value, FD_AGG_OUT)))
		return (print_bool_sep_error(ERR_SYNTAX, cursor, false));
	else if (cursor->type == TOKEN_LT && (!ft_strequ(cursor->value, REDIR_IN)
			&& !ft_strequ(cursor->value, REDIR_HEREDOC)))
		return (print_bool_sep_error(ERR_SYNTAX, cursor, false));
	if (!(cursor->next)
		|| !(cursor->next->type & (TOKEN_WORD | TOKEN_WHITESPACE)))
		return (print_bool_syntax_error(ERR_SYNTAX, cursor, false));
	if (cursor->next->type == TOKEN_WORD && !check_syntax_after_op(cursor))
		return (false);
	if (cursor->next->type == TOKEN_WHITESPACE
		&& (!(cursor->next->next) || cursor->next->next->type != TOKEN_WORD))
		return (print_bool_syntax_error(ERR_SYNTAX, cursor->next, false));
	if (cursor->next->type == TOKEN_WHITESPACE && cursor->next->next
		&& !check_syntax_after_op(cursor->next))
		return (false);
	return (true);
}
