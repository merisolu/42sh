/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:03:39 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 13:39:38 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	on_error(char c)
{
	ft_dprintf(STDERR_FILENO, "42sh: fc: -%c: invalid option\n", c);
	ft_putstr_fd("fc: usage: fc [-e ename] [-nlr] or fc -s\n", STDERR_FILENO);
}

static int	launch_editor(char *const *args, char *flags, t_fc_range *range,
							t_state *state)
{
	if (!ft_strchr(flags, 'e'))
	{
		if (!cmd_fc_history_edit(
				env_get_or("FCEDIT", "vi", state->env), range, state))
			return (1);
		return (0);
	}
	if (!args[2])
	{
		ft_putstr_fd(
			"42sh: fc: -e: option requires an argument\n", STDERR_FILENO);
		ft_putstr_fd(
			"fc: usage: fc [-e ename] [-nlr] or fc -s\n", STDERR_FILENO);
		return (2);
	}
	else if (!cmd_fc_history_edit(args[2], range, state))
		return (1);
	return (0);
}

// TODO: Make sure this runs okay, even if the full default 16 entries cannot be displayed.
static void	print_history(bool show_numbers, t_fc_range *range,
	t_state *state)
{
	int	i;

	i = range->start;
	while (1)
	{
		if (show_numbers)
			ft_printf("%d", i);
		ft_printf("\t%s\n",
			state->history[cmd_fc_range_number_to_index(i, state)]);
		if (i == range->end)
			break ;
		if (range->start > range->end)
			i--;
		else
			i++;
	}
}

int	cmd_fc(char *const *args, t_state *state)
{
	int			editor_return_value;
	char		flags[6];
	t_fc_range	range;
	int			offset;

	offset = parse_flags(args + 1, "elnrs", flags, &on_error);
	cmd_fc_parse_range(args + offset + 1, flags, &range, state);
	if (ft_strchr(flags, 'r'))
		cmd_fc_reverse_range(&range);
	if (ft_strchr(flags, 'l'))
	{
		print_history(!ft_strchr(flags, 'n'), &range, state);
		return (0);
	}
	else
	{
		if (!ft_strchr(flags, 's'))
		{
			editor_return_value = launch_editor(args, flags, &range, state);
			if (editor_return_value != 0)
				return (editor_return_value);
		}
		cmd_fc_read_and_execute_file(state);
	}
	return (0);
}
