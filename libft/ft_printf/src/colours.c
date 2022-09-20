/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:21:09 by amann             #+#    #+#             */
/*   Updated: 2022/03/15 10:53:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_colour_code(size_t i)
{
	char	*colour_code_arr[9];

	colour_code_arr[0] = RED;
	colour_code_arr[1] = BLACK;
	colour_code_arr[2] = GREEN;
	colour_code_arr[3] = YELLOW;
	colour_code_arr[4] = BLUE;
	colour_code_arr[5] = PURPLE;
	colour_code_arr[6] = CYAN;
	colour_code_arr[7] = WHITE;
	colour_code_arr[8] = RESET_COLOUR;
	ft_putstr(colour_code_arr[i]);
}

static size_t	check_colour_loop(const char *s, size_t len)
{
	size_t	i;
	char	*colour_str_arr[9];

	colour_str_arr[0] = "{red}";
	colour_str_arr[1] = "{black}";
	colour_str_arr[2] = "{green}";
	colour_str_arr[3] = "{yellow}";
	colour_str_arr[4] = "{blue}";
	colour_str_arr[5] = "{purple}";
	colour_str_arr[6] = "{cyan}";
	colour_str_arr[7] = "{white}";
	colour_str_arr[8] = "{reset}";
	i = 0;
	while (i < 9)
	{
		if (!ft_strncmp(s, colour_str_arr[i], len))
		{
			print_colour_code(i);
			break ;
		}
		i++;
	}
	return (i);
}

static size_t	set_len(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '}' && len < 8)
		len++;
	return (len);
}

void	check_colour(const char *s, size_t *cursor, int *printf_ret)
{
	size_t	i;
	size_t	len;

	len = set_len(s);
	if (len < 8 && len > 3)
	{
		i = check_colour_loop(s, len);
		if (i < 9)
		{
			*cursor += len;
			return ;
		}
	}
	ft_printf_putchar("{", 1, printf_ret);
}
