/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:03:39 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/28 13:40:20 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	on_error(char c)
{
	ft_dprintf(STDERR_FILENO, "21sh: fc: -%c: invalid option\n", c);
	ft_putstr_fd("fc: usage: fc [-nl] or fc -s\n", STDERR_FILENO);
}

static int	get_start_index(t_state *state)
{
	int	i;

	i = 1;
	while (ft_strlen(state->history[i]) > 0 && i < HISTORY_SIZE - 1)
		i++;
	return (i - 1);
}

void	print_history(bool show_numbers, t_state *state)
{
	int	i;
	int	start;

	start = get_start_index(state);
	i = start;
	if (start > 16)
		i -= start - 16;
	while (i > 0)
	{
		if (show_numbers)
			ft_printf("%d\t%s\n", (start - i) + 1, state->history[i]);
		else
			ft_printf("\t%s\n", state->history[i]);
		i--;
	}
}

int	cmd_fc(char *const *args, t_state *state)
{
	char	flags[6];

	parse_flags(args + 1, "lns", flags, &on_error);
	if (ft_strchr(flags, 's'))
	{
		ft_putstr(state->history[1]);
		ft_strclr(state->input_context.input);
		ft_strcpy(state->input_context.input, state->history[1]);
		tokenize_and_execute(state);
		return (0);
	}
	if (ft_strchr(flags, 'l'))
		print_history(!ft_strchr(flags, 'n'), state);
	return (0);
}
