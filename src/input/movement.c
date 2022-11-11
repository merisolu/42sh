/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:58:25 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/09 15:17:17 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// int	handle_history(char buf[BUF_SIZE], t_state *state)
// {
// 	if (ft_strnequ(buf, ARROW_UP, ft_strlen(ARROW_UP)))
// 		history_recall(1, state);
// 	else if (ft_strnequ(buf, ARROW_DOWN, ft_strlen(ARROW_DOWN)))
// 		history_recall(-1, state);
// 	else
// 		return (0);
// 	return (3);
// }

int	handle_left(t_input_context *ctx)
{
	if (ctx->cursor > 0)
		ctx->cursor--;
	while (ctx->cursor > 0 && ctx->input[ctx->cursor] == '\n')
		ctx->cursor--;
	return (1);
}

int	handle_right(t_input_context *ctx)
{
	if (ctx->cursor + 1 <= ft_strlen(ctx->input))
		ctx->cursor++;
	while (ctx->cursor + 1
		<= ft_strlen(ctx->input) && ctx->input[ctx->cursor] == '\n')
		ctx->cursor++;
	return (1);
}

int	handle_home(t_input_context *ctx)
{
	ctx->cursor = 0;
	return (1);
}

int	handle_end(t_input_context *ctx)
{
	ctx->cursor = ft_strlen(ctx->input);
	return (1);
}
