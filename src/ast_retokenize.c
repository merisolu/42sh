/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_retokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:21:06 by amann             #+#    #+#             */
/*   Updated: 2022/10/24 19:19:45 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_token_dispatch	*get_parse_token_dispatch(void)
{
	static const t_token_dispatch	dispatch_table[] = {
	{'$', TOKEN_DOLLAR},
	{'~', TOKEN_TILDE},
	{'"', TOKEN_DOUBLE_QUOTE},
	{'\'', TOKEN_SINGLE_QUOTE},
	{'{', TOKEN_CURLY_OPEN},
	{'}', TOKEN_CURLY_CLOSED},
	{'+', TOKEN_PLUS},
	{'-', TOKEN_MINUS},
	{':', TOKEN_COLON},
	{'/', TOKEN_FWD_SLASH},
	{'=', TOKEN_EQUALS},
	{'\0', TOKEN_NULL}
	};

	return (dispatch_table);
}

static t_token_type	get_parser_token_type(char value)
{
	const t_token_dispatch	*dispatch_table;
	size_t					i;

	dispatch_table = get_parse_token_dispatch();
	i = 0;
	while (dispatch_table[i].token != TOKEN_NULL)
	{
		if (dispatch_table[i].symbol == value)
			return (dispatch_table[i].token);
		i++;
	}
	if (ft_is_whitespace(value))
		return (TOKEN_WHITESPACE);
	return (TOKEN_WORD);
}

t_token	*ast_retokenize(char *line)
{
	t_token			*result;
	t_token_type	type;
	int				i;
	int				buff_idx;
	char			*buff;

	buff = ft_strnew(ft_strlen(line) + 1);
	if (!buff)
		return (NULL);
	result = NULL;
	type = get_parser_token_type(line[0]);
	i = 0;
	buff_idx = 0;
	while (line[i])
	{
		if (get_parser_token_type(line[i]) != type)
		{
			token_add(&result, type, ft_strdup(buff));
			ft_bzero(buff, ft_strlen(buff) + 1);
			type = get_parser_token_type(line[i]);
			buff_idx = 0;
		}
		buff[buff_idx] = line[i];
		buff_idx++;
		i++;
	}
	token_add(&result, type, ft_strdup(buff));
	free(buff);
	return (result);
}
