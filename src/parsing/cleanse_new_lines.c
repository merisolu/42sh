/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanse_new_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:38:12 by amann             #+#    #+#             */
/*   Updated: 2023/02/22 15:42:30 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	remove_new_line(t_token *list, int i)
{
	char	*str;
	char	*str2;

	str = ft_strdelchar(list->value, i);
	str2 = ft_strdelchar(str, i);
	free(list->value);
	free(str);
	list->value = str2;
}

void	cleanse_new_lines(t_token *list)
{
	t_tokenizer	tokenizer;
	int			i;

	while (list)
	{
		if (list->type == TOKEN_WORD)
		{
			ft_bzero(&tokenizer, sizeof(tokenizer));
			i = 0;
			while ((list->value)[i + 1])
			{
				check_quotes((list->value)[i], &tokenizer);
				if ((list->value)[i] == '\\' && (list->value)[i + 1] == '\n'
					&& !(tokenizer.in_quotes && tokenizer.quote_type == '\''))
					remove_new_line(list, i);
				i++;
			}
		}
		list = list->next;
	}
}
