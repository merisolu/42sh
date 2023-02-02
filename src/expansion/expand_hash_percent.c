/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hash_percent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:34:43 by amann             #+#    #+#             */
/*   Updated: 2023/02/02 12:58:32 by amann            ###   ########.fr       */
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

static void	handle_hash(char *temp_res, char *temp_exp)
{
	size_t	len;
	size_t	res_len;

	len = ft_strlen(temp_exp);
	res_len = ft_strlen(temp_res);
	if (len != 0 && len <= res_len
		&& (ft_strnequ(temp_res, temp_exp, len)))
	{
		ft_memmove((void *)temp_res, (void *)temp_res + len, res_len);
		ft_strclr(temp_res + res_len);
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

int	expand_hash_percent(t_token **cursor, t_state *state, char **res, t_token *param)
{
	char	*temp_res;
	char	*temp_exp;
	int		return_code;
	bool	hash;

	hash = (*cursor)->previous->type == TOKEN_HASH;
	temp_exp = NULL;
	if ((*cursor)->type == TOKEN_WHITESPACE)
	{
		temp_exp = ft_strdup((*cursor)->value);
		*cursor = (*cursor)->next;
	}
	temp_res = NULL;
	set_braces_state(state);
	expand_name(param->value, state, &temp_res);
	expansions_loop(cursor, state, &temp_exp, true);
	if (hash)
		handle_hash(temp_res, temp_exp);
	else
		handle_percent(temp_res, temp_exp);
	return_code = add_to_result(res, temp_res, state);
	free(temp_res);
	free(temp_exp);
	return (0);
}
