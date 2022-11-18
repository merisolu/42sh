/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:03:39 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/18 14:37:45 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	on_error(char c)
{
	ft_dprintf(STDERR_FILENO, "fc: -%c: invalid option\nfc: usage: fc [-nl]\n",
		c);
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
	int		i;

	(void)state;
	i = parse_flags(args + 1, "elnrs", flags, &on_error) + 1;
	if (ft_strchr(flags, 'l'))
		print_history(!ft_strchr(flags, 'n'), state);
	return (0);
}
