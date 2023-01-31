/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:33:53 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/31 12:42:18 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

char	*cmd_fc_parse_replacement(char *arg)
{
	if (ft_strchr(arg, '='))
		return (arg);
	return (NULL);
}

char	*cmd_fc_apply_replacement(char *src, char *spec)
{
	char	*result;
	char	*target;
	char	*replacement;

	if (ft_dstchr(spec, '=', ft_strlen(spec)) == 0)
		return (ft_strreplace(src, "", ""));
	target = ft_strndup(spec, ft_dstchr(spec, '=', ft_strlen(spec)));
	replacement = ft_strdup(spec + ft_dstchr(spec, '=', ft_strlen(spec)) + 1);
	if (!target || !replacement)
	{
		free(target);
		free(replacement);
		return (NULL);
	}
	result = ft_strreplace(src, target, replacement);
	free(target);
	free(replacement);
	return (result);
}
