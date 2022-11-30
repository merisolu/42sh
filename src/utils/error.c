/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:57:03 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/30 14:07:37 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
 * Prints the given error message to stderr, and returns the given value.
 */

int	print_error_valist(int return_value, char *format, va_list list)
{
	ft_vdprintf(STDERR_FILENO, format, list);
	return (return_value);
}

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
