/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/18 15:51:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 * New process for merging quote handling and tokenisation.
 * Each character of the input string is added to a buffer until the token
 * type changes. The buffer is then added as a token to the token list.
 * We then bzero the buffer and start adding to it again, repeating the process
 * until we reach the end of the input string.
 *
 * In each iteration we check quotes. If we hit an opening or closing quote,
 * we flip the in_quotes variable and skip to the next character as these
 * should not form part of our WORD token. While we are 'in_quotes' (i.e. that
 * variable is TRUE), all characters in the string are interpreted literally -
 * so pipes and semicolons form part of a WORD, for example.
 *
 * If in_quotes is still TRUE at the end of the input string, we can enter
 * multi-line input mode.
 */


static int		check_quotes(char c, t_tokenizer *t)
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
