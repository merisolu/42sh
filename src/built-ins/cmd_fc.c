/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:03:39 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/09 12:24:06 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	on_error(char c)
{
	ft_dprintf(STDERR_FILENO, "42sh: fc: -%c: invalid option\n", c);
	ft_putstr_fd("fc: usage: fc [-e ename] [-nlr] or fc -s\n", STDERR_FILENO);
}

static int	get_start_index(t_state *state)
{
	int	i;

	i = 1;
	while (i < HISTORY_SIZE - 1 && ft_strlen(state->history[i]) > 0)
		i++;
	return (i - 1);
}

static int	launch_editor(char *const *args, char *flags, t_state *state)
{
	if (!ft_strchr(flags, 'e'))
	{
		if (!cmd_fc_history_edit(env_get_or("FCEDIT", "vi", state->env), state))
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
	else if (!cmd_fc_history_edit(args[2], state))
		return (1);
	return (0);
}

static void	print_history(bool show_numbers, bool reverse, t_state *state)
{
	int	i;
	int	start;
	int	end;

	start = get_start_index(state);
	i = start;
	if (start > 16)
		i -= start - 16;
	if (reverse)
		i = 1;
	end = 0;
	if (reverse)
		end = ft_min(start + 1, 17);
	while (i != end)
	{
		if (show_numbers)
			ft_printf("%d", (start - i) + 1);
		ft_printf("\t%s\n", state->history[i]);
		if (reverse)
			i++;
		else
			i--;
	}
}

int	cmd_fc(char *const *args, t_state *state)
{
	int		editor_return_value;
	char	flags[6];

	parse_flags(args + 1, "elnrs", flags, &on_error);
	if (ft_strchr(flags, 'l'))
	{
		print_history(!ft_strchr(flags, 'n'), ft_strchr(flags, 'r'), state);
		return (0);
	}
	else if (ft_strchr(flags, 'e') || ft_strchr(flags, 's')
		|| ft_strlen(flags) == 0)
	{
		if (!ft_strchr(flags, 's'))
		{
			editor_return_value = launch_editor(args, flags, state);
			if (editor_return_value != 0)
				return (editor_return_value);
		}
		ft_putstr(state->history[1]);
		ft_strclr(state->input_context.input);
		ft_strcpy(state->input_context.input, state->history[1]);
		tokenize_and_execute(state);
	}
	return (0);
}
