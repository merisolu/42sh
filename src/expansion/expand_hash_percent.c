/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hash_percent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:34:43 by amann             #+#    #+#             */
/*   Updated: 2023/02/16 13:26:52 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	handle_percent(char *temp_res, char *temp_exp)
{
	size_t	len;
	size_t	res_len;

	len = ft_strlen(temp_exp);
	res_len = ft_strlen(temp_res);
	if (len != 0 && len <= res_len
		&& (ft_strequ(temp_res + (res_len - len), temp_exp)))
		ft_strclr(temp_res + (res_len - len));
}

static void	handle_hash_glob(t_state *state, char *temp_res, char *temp_exp, \
		size_t res_len)
{
	int		i;
	size_t	len;

	len = ft_strlen(temp_exp);
	i = res_len - 1;
	if (!(state->t.last))
		i = 0;
	while (temp_res[i] && i >= 0)
	{
		if (ft_strnequ(temp_res + i, temp_exp, len))
		{
			ft_memmove((void *)temp_res, (void *)temp_res + i + len,
				res_len - i);
			ft_strclr(temp_res + res_len - i);
			return ;
		}
		if (!(state->t.last))
			i++;
		else
			i--;
	}
}

static void	handle_hash(t_state *state, char *temp_res, char *temp_exp)
{
	size_t	len;
	size_t	res_len;
	bool	glob;

	if (!temp_res || !temp_exp)
		return ;
	glob = false;
	if (temp_exp[0] == '*')
	{
		glob = true;
		temp_exp++;
	}
	len = ft_strlen(temp_exp);
	res_len = ft_strlen(temp_res);
	if (!glob && len != 0 && len <= res_len
		&& (ft_strnequ(temp_res, temp_exp, len)))
	{
		ft_memmove((void *)temp_res, (void *)temp_res + len, res_len);
		ft_strclr(temp_res + res_len);
		return ;
	}
	if (glob)
		handle_hash_glob(state, temp_res, temp_exp, res_len);
}

static void	position_cursor(t_token **cursor, t_state *state, char **temp, \
		bool hash)
{
	if ((*cursor)->type == TOKEN_WHITESPACE)
	{
		*temp = ft_strdup((*cursor)->value);
		*cursor = (*cursor)->next;
		return ;
	}
	if (((*cursor)->type == TOKEN_HASH && hash)
		|| ((*cursor)->type == TOKEN_PERCENT && !hash))
	{
		*cursor = (*cursor)->next;
		state->t.last = true;
	}
}

/*
	pattern matching, hash works from the start of the string, percent from the
	end.

	One char means shortest matching pattern, two means the longest.
	However, we do not need	to concern ourselves with this, the shell does not
	incorporate globbing, so patterns will not vary in length.

	First, we expand the param into a temp string
	Then we expand what follows the hash or percent token into another temp
	string
	We then take the length of the expansion and compare it to the start or
	end of the expanded param.
	If it matches, we truncate that respective part of the string
	We then append the result to res
*/

int	expand_hash_percent(t_token **cursor, t_state *state, char **res, \
		t_token *param)
{
	char	*temp_res;
	char	*temp_exp;
	int		return_code;
	bool	hash;

	hash = (*cursor)->previous->type == TOKEN_HASH;
	temp_exp = NULL;
	position_cursor(cursor, state, &temp_exp, hash);
	temp_res = NULL;
	set_braces_state(state);
	expand_name(param->value, state, &temp_res);
	expansions_loop(cursor, state, &temp_exp, true);
	if (hash)
		handle_hash(state, temp_res, temp_exp);
	else
		handle_percent(temp_res, temp_exp);
	return_code = add_to_result(res, temp_res, state);
	free(temp_res);
	free(temp_exp);
	return (0);
}
