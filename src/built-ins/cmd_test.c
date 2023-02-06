/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:21:29 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/06 13:27:41 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	check_unary(char *flag, char *arg, int invert)
{
	int		result;

	result = 0;
	if (flag[0] == '-' && ft_strlen(flag) == 2)
	{
		if (ft_strchr("bcdfgLpSu", flag[1]))
			result = cmd_test_does_file_type_match(arg, flag[1]);
		else if (ft_strchr("rwx", flag[1]))
			result = cmd_test_does_file_have_permission(arg, flag[1]);
		else if (flag[1] == 's')
			result = cmd_test_file_has_data(arg);
		else if (flag[1] == 'e')
			result = !(access(arg, F_OK) == 0);
		else if (flag[1] == 'z')
			result = !(ft_strlen(arg) == 0);
		else
			return (print_error(2, ERRTEMPLATE_DOUBLE_NAMED,
					"test", flag, "unary operator expected"));
	}
	else if (ft_strlen(flag) != 0)
		result = 1;
	if (invert)
		return (!result);
	return (result);
}

int	cmd_test(char *const *args, t_state *state)
{
	size_t	args_len;
	int		invert;

	(void)state;
	args_len = ft_null_array_len((void **)args + 1);
	if (args_len == 0)
		return (1);
	if (args_len == 1)
		return (ft_strlen(args[1]) == 0);
	invert = ft_strequ(args[1], "!");
	if (args_len - invert == 2)
		return (check_unary(args[1 + invert], args[2 + invert], invert));
	return (0);
}
