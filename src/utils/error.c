/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:57:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/15 18:04:02 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
 * Prints the given error message to stderr, and returns the given value.
 */
int	print_error(char *message, int return_value)
{
	ft_dprintf(STDERR_FILENO, "21sh: %s\n", message);
	return (return_value);
}

/*
 * Prints the given name and error message to stderr, and returns the
 * given return_value.
 */
int	print_named_error(char *name, char *message, int return_value)
{
	ft_dprintf(STDERR_FILENO, "21sh: %s: %s\n", name, message);
	return (return_value);
}

int	print_syntax_error(char *message, t_token *token, int return_value)
{
	if (token->next == NULL)
		ft_dprintf(STDERR_FILENO, "21sh: %s `newline'\n", message);
	else
		ft_dprintf(
			STDERR_FILENO,
			"21sh: %s `%s'\n",
			message,
			token->next->value
			);
	return (return_value);
}
