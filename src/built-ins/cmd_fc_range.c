/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:41:49 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/14 15:14:32 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	parse_string_range(char *arg, int length, t_state *state)
{
	int		i;
	size_t	arg_length;

	arg_length = ft_strlen(arg);
	i = 0;
	while (i < length)
	{
		if (ft_strnequ(state->history[i], arg, arg_length))
			return (history_index_to_number(i, state));
		i++;
	}
	return (-1);
}

static int	parse_numerical_range(char *arg, int length)
{
	return (ft_clamp(ft_atoi(arg), 1, length));
}

static int	parse_range(char *arg, int length, t_state *state)
{
	if (ft_strequ(arg, "-"))
		return (-1);
	if (ft_isdigit_str(arg) || (arg[0] == '-' && ft_isdigit_str(arg + 1)))
		return (parse_numerical_range(arg, length));
	return (parse_string_range(arg, length, state));
}

bool	cmd_fc_parse_range(char *const *args, char *flags, t_fc_range *range,
t_state *state)
{
	int	length;
	int	offset;

	offset = ft_strchr(flags, 'e') != NULL;
	length = get_history_length(state);
	if (!args[offset])
	{
		if (ft_strchr(flags, 'l'))
			range->start = ft_clamp(length - 15, 1, length);
		else
			range->start = length;
		range->end = length;
		return (true);
	}
	range->start = parse_range(args[offset], length, state);
	if (args[1 + offset])
		range->end = parse_range(args[1 + offset], length, state);
	else
		range->end = ft_clamp(range->start + 1, 1, length);
	if (range->start < 1 || range->end < 1)
		return (print_error_bool(false,
				ERRTEMPLATE_NAMED, "fc", ERR_HISTORY_SPEC_OUT_OF_RANGE));
	return (true);
}

void	cmd_fc_reverse_range(t_fc_range *range)
{
	int	temp;

	temp = range->start;
	range->start = range->end;
	range->end = temp;
}
