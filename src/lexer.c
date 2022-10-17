/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/17 18:10:28 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//expansions may need to happen after the construction of the AST, so tokens
//associated with these can be removed from this part of the process

static const t_token_dispatch	*get_token_dispatch(void)
{
	static const t_token_dispatch	dispatch_table[] = {
//	{'$', TOKEN_DOLLAR},
//	{'~', TOKEN_TILDE},
//	{'"', TOKEN_DOUBLE_QUOTE},
//	{'\'', TOKEN_SINGLE_QUOTE},
//	{'{', TOKEN_CURLY_OPEN},
//	{'}', TOKEN_CURLY_CLOSED},
//	{'+', TOKEN_PLUS},
//	{'-', TOKEN_MINUS},
	{'|', TOKEN_PIPE},
	{';', TOKEN_SEMICOLON},
	{'>', TOKEN_GT},
	{'<', TOKEN_LT},
	{'&', TOKEN_AMPERSAND},
	{'\\', TOKEN_BACKSLASH},
	{'\0', TOKEN_NULL}
	};

	return (dispatch_table);
}

static t_token_type	get_token_type(char value, int in_quotes)//, char quote_type)
{
	const t_token_dispatch	*dispatch_table;
	size_t					i;

	if (in_quotes)
	{
		return (TOKEN_WORD);
	}
	dispatch_table = get_token_dispatch();
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

//maybe add the quote checking process in here
//a TOKEN_WORD should be delimited by other tokens, but only when not in quotes.

//set up a buffer that is line len + 1
//copy chars into that buffer in accordance with quote logic
//pass buffer to token_add using ft_strdup instead of using ft_strsub...
//bzero the buffer

int		check_quotes(char c, int *in_quotes, char *quote_type)
{
	if ((c == '\'' || c == '\"') && !*in_quotes)
	{
		*in_quotes = TRUE;
		*quote_type = c;
		return (1);
	}
	else if (c == *quote_type && *in_quotes)
	{
		*in_quotes = FALSE;
		return (1);
	}
	return (0);
}

t_token	*tokenize(char *line)
{
	t_token			*result;
	t_token_type	type;
	int				i;
	int				in_quotes;
	char			quote_type;
	char			*buff;
	size_t			len;
	size_t			buff_idx;

	in_quotes = FALSE;
	quote_type = '\0';
	result = NULL;
	len = ft_strlen(line) + 1;
	buff = ft_strnew(sizeof(char) * len);
	i = 0;
	while (line[i] && get_token_type(line[i], FALSE) == TOKEN_WHITESPACE)
		i++;
	buff_idx = 0;
	type = get_token_type(line[i], FALSE);
	while (line[i])
	{
		if (!check_quotes(line[i], &in_quotes, &quote_type))
		{
			if (get_token_type(line[i], in_quotes) == type)
			{
				buff[buff_idx] = line[i];
				buff_idx++;
			}
			else
			{
				ft_printf("buff = %s\n", buff);
				token_add(&result, type, ft_strdup(buff));
				type = get_token_type(line[i + 1], in_quotes);
				ft_bzero(buff, len);
				buff_idx = 0;
			}
		}
		i++;
	}
	ft_printf("buff = %s\n", buff);
	token_add(&result, type, ft_strdup(buff));
	free(buff);
	return (result);
}
