/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:02:10 by amann             #+#    #+#             */
/*   Updated: 2022/12/20 17:31:14 by amann            ###   ########.fr       */
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

static char	*set_new_token_val(t_token *cursor, int i)
{
	if (i == 1)
	{
		if (cursor->type == TOKEN_GT)
			return (ft_strdup(REDIR_OUT));
		else
			return (ft_strdup(REDIR_IN));
	}
	else if (i == 2)
		return (ft_strdup("&"));
	else if (i == 3)
	{
		if (cursor->type == TOKEN_GT)
			return (ft_strdup(FD_AGG_OUT));
		else
			return (ft_strdup(FD_AGG_IN));
	}
	if (cursor->type == TOKEN_GT)
		return (ft_strdup(REDIR_APPEND));
	else
		return (ft_strdup(REDIR_HEREDOC));
}

static bool	contains_ampersand(t_token *cursor)
{
	int		i;
	char	*temp;

	i = 0;
	while ((cursor->value)[i])
	{
		if ((cursor->value)[i] == '&')
			break ;
		i++;
	}
	temp = set_new_token_val(cursor, i);
	if (!temp)
		return (print_bool_sep_error(ERR_SYNTAX, cursor, false));
	ft_strdel(&(cursor->value));
	cursor->value = temp;
	return (print_bool_sep_error(ERR_SYNTAX, cursor, false));
}

static bool	invalid_redir_token(t_token *cursor)
{
	if (ft_strchr(cursor->value, '&'))
		return (contains_ampersand(cursor));
	if (ft_strlen(cursor->value) == 3)
		(cursor->value)[1] = '\0';
	else
		(cursor->value)[2] = '\0';
	return (print_bool_sep_error(ERR_SYNTAX, cursor, false));
}

bool	check_redir_syntax(t_token *cursor)
{
	if (cursor->type == TOKEN_GT && (!ft_strequ(cursor->value, REDIR_OUT)
			&& !ft_strequ(cursor->value, REDIR_APPEND)
			&& !ft_strequ(cursor->value, FD_AGG_OUT)))
		return (invalid_redir_token(cursor));
	else if (cursor->type == TOKEN_LT && (!ft_strequ(cursor->value, REDIR_IN)
			&& !ft_strequ(cursor->value, REDIR_HEREDOC)))
		return (invalid_redir_token(cursor));
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
