/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:18:15 by amann             #+#    #+#             */
/*   Updated: 2023/01/05 15:58:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	print_bool_syntax_error(char *message, t_token *token, bool ret)
{
	if (!token)
		return (ret);
	if (token->next == NULL)
		ft_dprintf(STDERR_FILENO, "42sh: %s `newline'\n", message);
	else
	{
		ft_dprintf(
			STDERR_FILENO,
			"42sh: %s `%s'\n",
			message,
			token->next->value
			);
	}
	return (ret);
}

bool	print_bool_sep_error(char *message, t_token *token, bool ret)
{
	if (!token)
		return (ret);
	else
		ft_dprintf(
			STDERR_FILENO,
			"42sh: %s `%s'\n",
			message,
			token->value
			);
	return (ret);
}
