/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:33:53 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/21 14:01:04 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	cmd_fc_parse_replacements(char *const *args,
			char *result[FC_MAX_REPLACE])
{
	size_t	i;
	size_t	o;

	i = 0;
	while (ft_strchr(args[i], '='))
	{
		o = 0;
		while (o < FC_MAX_REPLACE && result[o])
			o++;
		result[o] = args[i];
		i++;
	}
}

static char	*apply_replacement(char *src, char *spec)
{
	char	*result;
	char	*target;
	char	*replacement;

	if (!spec || ft_dstchr(spec, '=', ft_strlen(spec)) == 0)
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
	free(src);
	return (result);
}

char	*cmd_fc_apply_replacements(char *src, char *spec[FC_MAX_REPLACE])
{
	char	*result;
	size_t	i;

	result = ft_strdup(src);
	i = 0;
	while (spec[i] && result)
	{
		result = apply_replacement(result, spec[i]);
		i++;
	}
	return (result);
}
