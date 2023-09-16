/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_into_buff.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2023/09/16 17:10:39 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
 * b-zeroes the char pointer before reading from stdin into it.
 * Includes error handling
 */
bool read_input_to_buff(char *buff)
{
	ssize_t	ret;

	ft_bzero(buff, INPUT_MAX_SIZE);
	ret = read(STDIN_FILENO, buff, BUF_SIZE);
	if (ret == -1)
		return (print_error_bool(false, "error: %s\n", ERR_READ_FAIL));
	while (ret)
	{
		ret = read(STDIN_FILENO, buff + ft_strlen(buff), BUF_SIZE);
		if (ret == -1)
			return (print_error_bool(false, "error: %s\n", ERR_READ_FAIL));
	}
	return (true);
}