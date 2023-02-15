/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:32:37 by amann             #+#    #+#             */
/*   Updated: 2023/02/15 17:40:16 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static bool	check_exp_is_dir(char *exp, size_t exp_len)
{
	char	*temp;
	bool	res;

	exp_len--;
	while (exp_len && exp[exp_len] != '/')
		exp_len--;
	temp = ft_strndup(exp, exp_len);
	if (!temp)
		return (false);
	res = ft_is_dir(temp);
	free(temp);
	if (res)
		return (true);
	return (false);
}

static void	insert_and_reposition(t_input_context *ctx, char *exp, \
		size_t start, size_t orig_len)
{
	size_t	exp_len;

	exp_len = ft_strlen(exp);
	ft_memmove((ctx->input) + start + exp_len, (ctx->input) + start + orig_len,
		ft_strlen((ctx->input) + start + orig_len));
	ft_memcpy((void *)((ctx->input) + start), (void *)exp, exp_len);
	if (orig_len > exp_len)
		ft_memmove((ctx->input) + start + exp_len,
			(ctx->input) + start + orig_len,
			ft_strlen((ctx->input) + start + exp_len));
	ctx->cursor += exp_len - orig_len;
}

void	insert_expansion(t_input_context *ctx, char *exp)
{
	size_t	start;
	size_t	exp_len;
	size_t	orig_len;

	exp_len = ft_strlen(exp);
	if (!check_exp_is_dir(exp, exp_len))
		return ;
	orig_len = 0;
	start = ctx->cursor;
	if (ctx->cursor > 0)
		start = ctx->cursor - 1;
	while (start && (ctx->input)[start] != ' ')
	{
		start--;
		orig_len++;
	}
	if (start != 0)
		start++;
	else
		orig_len++;
	if (ctx->cursor + (exp_len - orig_len) > INPUT_MAX_SIZE
		|| ft_strlen(ctx->input) + (exp_len - orig_len) > INPUT_MAX_SIZE)
		return ;
	insert_and_reposition(ctx, exp, start, orig_len);
}
