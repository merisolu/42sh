/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/22 15:39:20 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	skip_whitespace(char *line)
{
	int			i;
	t_tokenizer	t;

	ft_bzero((void *)&t, sizeof(t_tokenizer));
	i = 0;
	while (line[i] && get_token_type(line[i], &t) == TOKEN_WHITESPACE)
		i++;
	return (i);
}

static bool	tokenize_init(t_tokenizer *t, char *line)
{
	(void) line;
	ft_bzero(t, sizeof(t_tokenizer));
	t->quote_type = '\0';
	t->buff = ft_strnew(sizeof(char) * (ft_strlen(line) + 1));
	if (!(t->buff))
		return (print_error_bool(false, "\n42sh: %s\n", ERR_MALLOC_FAIL));
	return (true);
}

/*
 * While we are dealing with the same type of token, we keep appending chars
 * to the buffer.
 *
 * When we hit a token that differs, we append the buffer to our token list
 * and clear the buffer. The current token is then added to the start of the
 * buffer and the type is reset to its type.
 *
 * Exceptional case is that we are looking at an & when expecting a > or <
 * This is needed in situations when we are dealing with fd aggregation
 */

static bool	t_loop(char *lc, t_tokenizer *t, t_token_type *type, t_token **r)
{
	if (get_token_type(*lc, t) != *type
		&& !((*type == TOKEN_LT || *type == TOKEN_GT) && get_token_type(\
		*lc, t) == TOKEN_AMPERSAND))
	{
		if (!token_add(r, *type, ft_strdup(t->buff)))
		{
			ft_strdel(&(t->buff));
			return (print_error_bool(false, "\n42sh: %s\n", ERR_MALLOC_FAIL));
		}
		ft_bzero(t->buff, ft_strlen(t->buff) + 1);
		*type = get_token_type(*lc, t);
		t->buff_idx = 0;
	}
	(t->buff)[t->buff_idx] = *lc;
	(t->buff_idx)++;
	return (true);
}

t_token	*tokenize(char *input, t_tokenizer *t)
{
	t_token			*result;
	t_token_type	type;
	int				i;

	if (!tokenize_init(t, input))
		return (NULL);
	result = NULL;
	i = skip_whitespace(input);
	type = get_token_type(input[i], t);
	while (input[i] && t->buff)
	{
		check_quotes(input[i], t);
		t_loop(input + i, t, &type, &result);
		t->backslash_inhibited = \
			(input[i] == '\\' && !t->backslash_inhibited
				&& !(t->in_quotes && t->quote_type == '\''));
		i++;
	}
	if (t->buff && !token_add(&result, type, ft_strdup(t->buff)))
		print_error_ptr(NULL, "\n42sh: %s\n", ERR_MALLOC_FAIL);
	free(t->buff);
	cleanse_new_lines(result);
	return (result);
}
