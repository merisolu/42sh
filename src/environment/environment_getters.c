/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:52:18 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/30 15:27:11 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
 * Returns a pointer to an environment variable string with the given name
 * in the environment variable array. Returns NULL if nothing was found.
 */

char	**env_get_pointer(const char *name, char *const *env)
{
	size_t	i;
	size_t	name_length;
	size_t	env_name_length;

//	size_t len = ft_null_array_len((void **)env);
	if (!env)
		return (NULL);
	name_length = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		//ft_printf("envlen = %zu i = %d name = %s\n", len, i, env[i]);
//		ft_printf("env[%d] = %s max = %d\n",i, env[i], ft_strlen(env[i]));
		env_name_length = ft_dstchr(env[i], '=', ft_strlen(env[i]));
		if (env_name_length == name_length \
			&& ft_strncmp(env[i], name, env_name_length) == 0)
			return ((char **)env + i);
		i++;
	}
//	ft_putendl(name);
	return (NULL);
}

/*
 * Attempts to return the value of the environment variable matching the given
 * name. Returns NULL if nothing was found.
 */

char	*env_get(const char *name, char *const *env)
{
	char	**temp;

	temp = env_get_pointer(name, env);
	if (temp)
	{
		return (ft_strchr(*temp, '=') + 1);
	}
	return (NULL);
}

/*
 * Attempts to return the value of the environment variable matching the given
 * name. Returns on_fail if nothing was found.
 */

char	*env_get_or(char *name, char *on_fail, char *const *env)
{
	char	*temp;

	temp = env_get(name, env);
	if (temp)
		return (temp);
	return (on_fail);
}
