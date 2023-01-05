/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:03:39 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/05 15:58:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	on_error(char c)
{
	ft_dprintf(STDERR_FILENO, "42sh: fc: -%c: invalid option\n", c);
	ft_putstr_fd("fc: usage: fc [-nlr] or fc -s\n", STDERR_FILENO);
}

static int	get_start_index(t_state *state)
{
	int	i;

	i = 1;
	while (i < HISTORY_SIZE - 1 && ft_strlen(state->history[i]) > 0)
		i++;
	return (i - 1);
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
	char	flags[6];

	parse_flags(args + 1, "lnrs", flags, &on_error);
	if (ft_strchr(flags, 's'))
	{
		ft_putstr(state->history[1]);
		ft_strclr(state->input_context.input);
		ft_strcpy(state->input_context.input, state->history[1]);
		tokenize_and_execute(state);
		return (0);
	}
	if (ft_strchr(flags, 'l'))
		print_history(!ft_strchr(flags, 'n'), ft_strchr(flags, 'r'), state);
	return (0);
}
