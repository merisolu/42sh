/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:22:18 by amann             #+#    #+#             */
/*   Updated: 2023/01/03 17:35:21 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
 * If variables are declared at the start of a command, these should be
 * temporarily added to the environment for that command. After the commmand
 * has finished executing these will be removed.
 *
 * The while loop is basically lifted straight out of the env builtin.
 * We know at this point the parser has validated the var_list, we can just do
 * a little pointer magic and let env_set take care of updating the env array.
 */

static void	add_orig_to_var_list(char **orig_val, char ***var_list, int i)
{
	ft_strdel(&(*var_list)[i]);
	(*var_list)[i] = ft_strdup(*orig_val);
	ft_strdel(orig_val);
}

bool	update_env_execution(t_state *state, t_ast_context *ctx)
{
	char	*pair;
	char	*temp;
	char	**orig;
	char	*orig_val;
	int		i;

	if (!ctx->node->left->var_list)
		return (true);
	i = 0;
	while ((ctx->node->left->var_list)[i])
	{
		pair = (ctx->node->left->var_list)[i];
		temp = ft_strchr(pair, '=') + 1;
		pair[ft_dstchr(pair, '=', ft_strlen(pair))] = '\0';
		orig = env_get_pointer((ctx->node->left->var_list)[i], state->env);
		if (orig)
			orig_val = ft_strdup(*orig);
		if (!env_set(pair, temp, &(state->env)))
			return (false);
		if (orig)
			add_orig_to_var_list(&orig_val, &(ctx->node->left->var_list), i);
		i++;
	}
	return (true);
}
