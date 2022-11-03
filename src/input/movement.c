/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:58:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/03 13:40:03 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// static int	handle_history(char buf[BUF_SIZE], t_state *state)
// {
// 	if (ft_strnequ(buf, ARROW_UP, ft_strlen(ARROW_UP)))
// 		history_recall(1, state);
// 	else if (ft_strnequ(buf, ARROW_DOWN, ft_strlen(ARROW_DOWN)))
// 		history_recall(-1, state);
// 	else
// 		return (0);
// 	return (3);
// }

static int	handle_cursor(char buf[BUF_SIZE], t_input_context *ctx)
{
	if (ft_strnequ(buf, ARROW_LEFT, ft_strlen(ARROW_LEFT)))
	{
		if (ctx->cursor > 0)
			ctx->cursor--;
		while (ctx->cursor > 0 && ctx->input[ctx->cursor] == '\n')
			ctx->cursor--;
	}
	else if (ft_strnequ(buf, ARROW_RIGHT, ft_strlen(ARROW_RIGHT)))
	{
		if (ctx->cursor + 1 <= ft_strlen(ctx->input))
			ctx->cursor++;
		while (ctx->cursor + 1
			<= ft_strlen(ctx->input) && ctx->input[ctx->cursor] == '\n')
			ctx->cursor++;
	}
	else if (ft_strnequ(buf, HOME_KEY, ft_strlen(HOME_KEY)))
		ctx->cursor = 0;
	else if (ft_strnequ(buf, END_KEY, ft_strlen(END_KEY)))
		ctx->cursor = ft_strlen(ctx->input);
	else
		return (0);
	return (3);
}

// TODO: Missing
	// {ARROW_UP, &handle_history},
	// {ARROW_DOWN, &handle_history},
static t_movement_handler_dispatch	*get_dispatch_table(void)
{
	static const t_movement_handler_dispatch	dispatch_table[] = {
	{ARROW_LEFT, &handle_cursor},
	{ARROW_RIGHT, &handle_cursor},
	{HOME_KEY, &handle_cursor},
	{END_KEY, &handle_cursor},
	{ARROW_UP_ALT, &handle_alt_up},
	{ARROW_DOWN_ALT, &handle_alt_down},
	{ARROW_LEFT_ALT, &handle_alt_left_right},
	{ARROW_RIGHT_ALT, &handle_alt_left_right},
	{0, NULL}
	};

	return ((t_movement_handler_dispatch *)dispatch_table);
}

int	check_movement(char *buf, t_input_context *ctx)
{
	size_t						i;
	t_movement_handler_dispatch	*dispatch_table;

	dispatch_table = get_dispatch_table();
	if (buf[0] != 0x1B)
		return (0);
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strnequ(dispatch_table[i].activator, buf,
				ft_strlen(dispatch_table[i].activator)))
			return (dispatch_table[i].run(buf, ctx));
		i++;
	}
	return (0);
}
