/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:03:39 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/14 14:09:27 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	on_error(char c)
{
	ft_dprintf(STDERR_FILENO, "42sh: fc: -%c: invalid option\n", c);
	ft_putstr_fd(FC_USAGE, STDERR_FILENO);
}

static int	edit_and_execute(char *const *args, char *flags, t_fc_range *range,
							t_state *state)
{
	if (!ft_strchr(flags, 'e'))
	{
		if (!cmd_fc_history_edit(
				env_get_or("FCEDIT", "vi", state->env), range, state))
			return (1);
		return (cmd_fc_read_and_execute_file(state));
	}
	if (!args[2])
	{
		ft_putstr_fd(
			"42sh: fc: -e: option requires an argument\n", STDERR_FILENO);
		ft_putstr_fd(FC_USAGE, STDERR_FILENO);
		return (2);
	}
	else if (!cmd_fc_history_edit(args[2], range, state))
		return (1);
	return (cmd_fc_read_and_execute_file(state));
}

static int	execute_from_history(t_fc_range *range, char *replace,
								t_state *state)
{
	int		i;
	char	*temp;

	i = range->start;
	while (1)
	{
		ft_strclr(state->input_context.input);
		temp = cmd_fc_apply_replacement(
				state->history[history_number_to_index(i, state)],
				replace);
		if (!temp)
			return (print_error(1, ERRTEMPLATE_NAMED, "fc", ERR_MALLOC_FAIL));
		ft_strncpy(state->input_context.input, temp, INPUT_MAX_SIZE);
		free(temp);
		ft_putstr(state->input_context.input);
		tokenize_and_execute(state);
		if (i == range->end)
			break ;
		if (range->start > range->end)
			i--;
		else
			i++;
	}
	return (state->last_return_value);
}

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
			state->history[history_number_to_index(i, state)]);
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
	char		flags[6];
	t_fc_range	range;
	int			offset;
	char		*replace;

	offset = cmd_fc_parse_flags(args + 1, "elnrs", flags, &on_error);
	if (offset == -1)
		return (1);
	replace = cmd_fc_parse_replacement(*(args + offset + 1));
	if (!cmd_fc_parse_range(args + offset + (replace != NULL) + 1, flags,
			&range, state))
		return (1);
	if (ft_strchr(flags, 'r'))
		cmd_fc_reverse_range(&range);
	if (ft_strchr(flags, 'l'))
		print_history(!ft_strchr(flags, 'n'), &range, state);
	else
	{
		if (!ft_strchr(flags, 's'))
			return (edit_and_execute(args, flags, &range, state));
		return (execute_from_history(&range, replace, state));
	}
	return (0);
}
