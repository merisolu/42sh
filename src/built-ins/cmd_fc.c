/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:03:39 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/24 10:38:11 by jumanner         ###   ########.fr       */
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

static int	execute_from_history(t_fc_range *range,
								char *replace[FC_MAX_REPLACE], t_state *state)
{
	int		i;
	char	*temp;

	i = range->start;
	while (1)
	{
		clear_input(&(state->input_context));
		temp = cmd_fc_apply_replacements(
				state->history[history_number_to_index(i, state)],
				replace);
		if (!temp)
			return (print_error(1, ERRTEMPLATE_NAMED, "fc", ERR_MALLOC_FAIL));
		ft_strncpy(state->input_context.input, temp, INPUT_MAX_SIZE);
		free(temp);
		ft_putendl_fd(state->input_context.input, STDERR_FILENO);
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

static int	print_history(bool show_numbers, t_fc_range *range,
	t_state *state)
{
	int	i;

	i = range->start;
	while (1)
	{
		if (show_numbers)
			ft_printf("%d", i);
		ft_printf("\t %s\n",
			state->history[history_number_to_index(i, state)]);
		if (i == range->end)
			break ;
		if (range->start > range->end)
			i--;
		else
			i++;
	}
	return (0);
}

int	cmd_fc(char *const *args, t_state *state)
{
	char		flags[6];
	t_fc_range	range;
	int			offset;
	char		*replace[FC_MAX_REPLACE];

	ft_bzero(replace, sizeof(char *) * FC_MAX_REPLACE);
	offset = cmd_fc_parse_flags(args + 1, "elnrs", flags, &on_error);
	if (offset == -1)
		return (1);
	if (ft_strchr(flags, 's'))
		cmd_fc_parse_replacements(args + offset + 1, replace);
	if (!cmd_fc_parse_range(args + offset + \
		ft_null_array_len((void **)replace) + 1, flags, &range, state))
		return (1);
	if (cmd_fc_check_empty_history_errors(state, flags))
		return (1);
	if (ft_strchr(flags, 'r'))
		cmd_fc_reverse_range(&range);
	if (ft_strchr(flags, 'l'))
		return (print_history(!ft_strchr(flags, 'n'), &range, state));
	if (!ft_strchr(flags, 's'))
		return (edit_and_execute(args, flags, &range, state));
	return (execute_from_history(&range, replace, state));
}
