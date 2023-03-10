/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:50:42 by amann             #+#    #+#             */
/*   Updated: 2023/02/23 11:43:19 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	hash_glob_only(t_state *state, char *temp_res)
{
	if (state->t.last)
		ft_strclr(temp_res);
	return ;
}

static void	handle_hash_glob(t_state *state, char *temp_res, char *temp_exp, \
		size_t res_len)
{
	int		i;
	size_t	len;

	len = ft_strlen(temp_exp);
	if (len == 0)
		return (hash_glob_only(state, temp_res));
	i = res_len - 1;
	if (!(state->t.last))
		i = 0;
	while (temp_res[i] && i >= 0)
	{
		if (ft_strnequ(temp_res + i, temp_exp, len))
		{
			ft_memmove((void *)temp_res, (void *)(temp_res + i + len),
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

void	handle_hash_expansion(t_state *state, char *temp_res, char *temp_exp)
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
		ft_memmove((void *)temp_res, (void *)(temp_res + len),
			ft_strlen(temp_res + len));
		ft_strclr(temp_res + (res_len - len));
		return ;
	}
	if (glob)
		handle_hash_glob(state, temp_res, temp_exp, res_len);
}
