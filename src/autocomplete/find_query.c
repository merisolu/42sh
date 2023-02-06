/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_query.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:54:23 by amann             #+#    #+#             */
/*   Updated: 2023/02/06 17:38:40 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static char	*find_query_loop(int len, char *str, char c)
{
	int	start;

	start = 0;
	while (len > -1)
	{
		if (str[len] == c)
		{
			start = len + 1;
			break ;
		}
		len--;
	}
	return (ft_strdup(str + start));
}

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

static void	insert_expansion(t_input_context *ctx, char *exp)
{
	size_t	start;
	size_t	exp_len;
	size_t	orig_len;

	exp_len = ft_strlen(exp);
	if (!check_exp_is_dir(exp, exp_len))
		return ;
	orig_len = 0;
	start = ctx->cursor;
	while (start && (ctx->input)[start] != ' ')
	{
		start--;
		orig_len++;
	}
	if (start != 0)
		start++;
	ft_memmove((ctx->input) + start + exp_len, (ctx->input) + start + orig_len,
		orig_len);
	ft_memcpy((void *)((ctx->input) + start), (void *)exp, exp_len);
	ctx->cursor += exp_len - orig_len;
	if (start != 0)
		ctx->cursor += 1;
}

char	*find_query(char *str, char c, t_state *state, bool expand)
{
	char	*last_word;
	char	*res;
	bool	var;

	last_word = find_query_loop((int)ft_strlen(str), str, ' ');
	if (!last_word)
		return (NULL);
	if (expand)
	{
		var = last_word[0] == '$';
		if (!expand_node(&last_word, state))
		{
			free(last_word);
			return (NULL);
		}
		if (var)
			insert_expansion(&(state->input_context), last_word);
	}
	if (c == ' ')
		return (last_word);
	res = find_query_loop((int)ft_strlen(last_word), last_word, c);
	free(last_word);
	if (!res)
		return (NULL);
	return (res);
}
