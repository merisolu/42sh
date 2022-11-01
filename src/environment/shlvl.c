/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:16:30 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 12:47:01 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void	print_shlvl_error(int target_shlvl)
{
	ft_dprintf(STDERR_FILENO,
		"21sh: warning: shell level (%d) too high, resetting to 1\n",
		target_shlvl);
}

int	set_shlvl(char *const **env)
{
	int		result;
	int		shlvl;
	char	*shlvl_string;

	shlvl = 0;
	if (env_get("SHLVL", *env))
		shlvl = ft_atoi(env_get("SHLVL", *env));
	if (shlvl + 1 < 0)
		shlvl = 0;
	else if (shlvl + 1 >= 1000)
	{
		print_shlvl_error(shlvl + 1);
		shlvl = 1;
	}
	else
		shlvl++;
	shlvl_string = ft_itoa(shlvl);
	if (!shlvl_string)
		return (print_error(ERR_MALLOC_FAIL, 0));
	result = env_set("SHLVL", shlvl_string, env);
	free(shlvl_string);
	return (result);
}
