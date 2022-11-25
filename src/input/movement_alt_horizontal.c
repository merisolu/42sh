/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_alt_horizontal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:52:11 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/25 13:52:34 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	handle_alt_left(t_input_context *ctx)
{
	size_t	start_limit;
	size_t	offset;
	size_t	end_limit;
	int		delta;

	start_limit = 0;
	end_limit = ft_strlen(ctx->input);
	offset = 1;
	delta = -1;
	while (ctx->cursor + delta >= start_limit
		&& ctx->cursor + delta < end_limit
		&& !ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	while (ctx->cursor + delta >= start_limit
		&& ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	return (1);
}

int	handle_alt_right(t_input_context *ctx)
{
	size_t	start_limit;
	size_t	offset;
	size_t	end_limit;
	int		delta;

	start_limit = 0;
	end_limit = ft_strlen(ctx->input);
	offset = 0;
	delta = 1;
	while (ctx->cursor + delta >= start_limit
		&& ctx->cursor + delta < end_limit
		&& !ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	while (ctx->cursor + delta >= start_limit
		&& ft_isalnum(ctx->input[ctx->cursor - offset]))
		ctx->cursor += delta;
	return (1);
}
