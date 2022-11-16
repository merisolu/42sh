/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:05:38 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 14:39:44 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	copy_word(t_input_context *ctx)
{
	size_t	start;
	size_t	end;

	if (!(ft_strlen(ctx->input) > 0 && ctx->cursor > 0))
		return (0);
	get_word_at_cursor(ctx, &start, &end);
	ft_strncpy(ctx->clipboard, ctx->input + start, end - start + 1);
	ctx->clipboard[end - start + 1] = '\0';
	return (1);
}

int	copy_to_cursor(t_input_context *ctx)
{
	ft_strncpy(ctx->clipboard, ctx->input, ctx->cursor);
	ctx->clipboard[ctx->cursor] = '\0';
	return (1);
}

int	copy_from_cursor(t_input_context *ctx)
{
	ft_strncpy(ctx->clipboard, ctx->input + ctx->cursor,
		ft_strlen(ctx->input + ctx->cursor));
	ctx->clipboard[ft_strlen(ctx->input + ctx->cursor)] = '\0';
	return (1);
}
