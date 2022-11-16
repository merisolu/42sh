/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:56:43 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 14:39:44 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	get_word_at_cursor(t_input_context *ctx, size_t *start, size_t *end)
{
	size_t	len;

	if (!start || !end)
		return ;
	len = ft_strlen(ctx->input);
	*end = ctx->cursor - 1;
	*start = *end;
	while (*start > 0 && *start < len && ft_is_whitespace(ctx->input[*start]))
		(*start)--;
	while (*start > 0 && *start < len && !ft_is_whitespace(ctx->input[*start]))
		(*start)--;
	if (*start > 0)
		(*start)++;
}
