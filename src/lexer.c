/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/18 15:29:44 by amann            ###   ########.fr       */
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

int		check_quotes(char c, t_tokenizer *t)
{
	if ((c == '\'' || c == '\"') && !(t->in_quotes))
	{
		t->in_quotes = TRUE;
		t->quote_type = c;
		return (1);
	}
	else if (c == t->quote_type && t->in_quotes)
	{
		t->in_quotes = FALSE;
		return (1);
	}
	return (0);
}

/*
 * New process for merging quote handling and tokenisation.
 * Each character of the input string is added to a buffer until the token type changes.
 * The buffer is then added as a token to the token list. We then bzero the buffer and start adding
 * to it again, repeating the process until we reach the end of the input string.
 *
 * In each iteration we check quotes. If we hit an opening or closing quote, we flip the in_quotes variable and skip
 * to the next character as these should not form part of our WORD token. While we are 'in_quotes' (i.e. that
 * variable is TRUE), all characters in the string are interpreted literally - so pipes and semicolons form part
 * of a WORD, for example.
 *
 * If in_quotes is still TRUE at the end of the input string, we can enter multi-line input mode.
 */

static int	skip_whitespace(char *line)
{
	int i;

	i = 0;
	while (line[i] && get_token_type(line[i], FALSE) == TOKEN_WHITESPACE)
		i++;
	return (i);
}

static int	tokenize_init(t_tokenizer *t, char *line)
{
	t->in_quotes = FALSE;
	t->quote_type = '\0';
	t->buff_idx = 0;
	t->buff = ft_strnew(sizeof(char) * (ft_strlen(line) + 1));
	if (!(t->buff))
		return (0);
	return (1);
}

static void t_loop(char *lc, t_tokenizer *t, t_token_type *type, t_token **r)
{
	if (get_token_type(*lc, t->in_quotes) == *type)
	{
		(t->buff)[t->buff_idx] = *lc;
		(t->buff_idx)++;
	}
	else
	{
		token_add(r, *type, ft_strdup(t->buff));
		*type = get_token_type(*(lc + 1), t->in_quotes);
		ft_bzero(t->buff, ft_strlen(t->buff) + 1);
		t->buff_idx = 0;
	}
}

t_token	*tokenize(char *line)
{
	t_token			*result;
	t_token_type	type;
	int				i;
	t_tokenizer		t;

	if (!tokenize_init(&t, line))
		return (NULL);
	result = NULL;
	i = skip_whitespace(line);
	type = get_token_type(line[i], FALSE);
	while (line[i])
	{
		if (!check_quotes(line[i], &t))
			t_loop(line + i, &t, &type, &result);
		i++;
	}
	token_add(&result, type, ft_strdup(t.buff));
	free(t.buff);
	return (result);
}
