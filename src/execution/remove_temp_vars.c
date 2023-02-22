/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_temp_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:24:53 by amann             #+#    #+#             */
/*   Updated: 2023/02/22 13:45:38 by jumanner         ###   ########.fr       */
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
			if (!export_set(pair, temp, &(state->env)))
				return (false);
		}
		else
			delete_var(var_list[i], &(state->env));
		i++;
	}
	return (true);
}
