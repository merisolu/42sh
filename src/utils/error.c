/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:57:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/20 13:06:40 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
 * Prints the given error message to stderr, and returns the given value.
 */

int	print_error(int return_value, char *format, ...)
{
	va_list	list;

	va_start(list, format);
	ft_vdprintf(STDERR_FILENO, format, list);
	va_end(list);
	return (return_value);
}

/*
 * Prints the given error message to stderr, and returns the given value.
 */

bool	print_error_bool(bool return_value, char *format, ...)
{
	va_list	list;

	va_start(list, format);
	ft_vdprintf(STDERR_FILENO, format, list);
	va_end(list);
	return (return_value);
}
