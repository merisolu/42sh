/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:49:56 by amann             #+#    #+#             */
/*   Updated: 2023/01/02 17:50:42 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	export_set(const char *name, const char *value, char *const **env)
{
	size_t	new_size;
	char	**destination_pointer;
	char	*new;

	if (ft_strisempty(name))
		return (1);
	destination_pointer = env_get_pointer(name, *env);
	if (!destination_pointer)
	{
		new_size = ft_null_array_len((void **)*env);
		destination_pointer = (char **)*env + new_size;
	}
	new = ft_strnew(ft_strlen(name) + 1 + ft_strlen(value));
	if (!new)
		return (print_error(0, ERRTEMPLATE_SIMPLE, ERR_MALLOC_FAIL));
	ft_strcpy(new, name);
	new[ft_strlen(name)] = '=';
	ft_strcpy(new + ft_strlen(name) + 1, value);
	free(*destination_pointer);
	*destination_pointer = new;
	return (1);
}
