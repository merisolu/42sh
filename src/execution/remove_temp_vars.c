/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_temp_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:24:53 by amann             #+#    #+#             */
/*   Updated: 2023/01/03 17:00:24 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	remove_temp_vars_from_env(t_ast_context *ctx, t_state *state)
{
	char	**var_list;
	char	*pair;
	char	*temp;
	int		i;

	var_list = ctx->node->left->var_list;
	i = 0;
	while (var_list[i])
	{
		if (ft_strchr(var_list[i], '='))
		{
			pair = var_list[i];
			temp = ft_strchr(pair, '=') + 1;
			pair[ft_dstchr(pair, '=', ft_strlen(pair))] = '\0';
			if (!env_set(pair, temp, &(state->env)))
				return (false);
		}
		else if (!env_unset(var_list[i], &(state->env)))
			return (false);
		i++;
	}
	return (true);
}
