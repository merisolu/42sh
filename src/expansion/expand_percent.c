/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:43:10 by amann             #+#    #+#             */
/*   Updated: 2023/02/20 17:07:24 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	handle_percent_glob(t_state *state, char *temp_res, \
		char *temp_exp, size_t res_len)
{
	int		i;
	size_t	len;

	len = ft_strlen(temp_exp) - 1;
	i = 0;
	if (!(state->t.last))
		i = res_len - 1;
	while (i >= 0 && temp_res[i])
	{
		if (ft_strnequ(temp_res + i, temp_exp, len))
		{
			ft_strclr(temp_res + i);
			return ;
		}
		if (!(state->t.last))
			i--;
		else
			i++;
	}
}

void	percent_glob_start(t_state *state, char *temp_res, char *temp_exp, \
		size_t res_len)
{
	size_t	exp_len;

	exp_len = ft_strlen(temp_exp);
	if (ft_strequ(temp_res + (res_len - exp_len), temp_exp))
	{
		if (state->t.last)
		{
			ft_strclr(temp_res);
			return ;
		}
		ft_strclr(temp_res + (res_len - exp_len));
	}
}

void	handle_percent(t_state *state, char *temp_res, char *temp_exp)
{
	size_t	len;
	size_t	res_len;
	bool	glob;

	if (!temp_res || !temp_exp)
		return ;
	len = ft_strlen(temp_exp);
	res_len = ft_strlen(temp_res);
	glob = false;
	if (temp_exp[len - 1] == '*')
		glob = true;
	if (temp_exp[0] == '*')
	{
		temp_exp++;
		percent_glob_start(state, temp_res, temp_exp, res_len);
		return ;
	}
	if (!glob && len != 0 && len <= res_len
		&& (ft_strequ(temp_res + (res_len - len), temp_exp)))
		ft_strclr(temp_res + (res_len - len));
	if (glob)
		handle_percent_glob(state, temp_res, temp_exp, res_len);
}
