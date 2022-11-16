/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_paste.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:21:42 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 11:06:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	paste(t_input_context *ctx)
{
	int	limit_reached;

	limit_reached = ft_strlen(ctx->input) + ft_strlen(ctx->clipboard)
		>= INPUT_MAX_SIZE;
	if (limit_reached)
		ctx->clipboard[INPUT_MAX_SIZE - ft_strlen(ctx->input)] = '\0';
	ft_memmove(
		ctx->input + ctx->cursor + ft_strlen(ctx->clipboard),
		ctx->input + ctx->cursor,
		ft_strlen(ctx->input + ctx->cursor));
	ft_memcpy(ctx->input + ctx->cursor, ctx->clipboard,
		ft_strlen(ctx->clipboard));
	ctx->cursor += ft_strlen(ctx->clipboard);
	if (limit_reached)
		ft_putstr(tgetstr("bl", NULL));
	return (1);
}
