/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:14:18 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/30 16:32:15 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
 * New process for merging quote handling and tokenisation.
 *
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
 *
 * If we're currently backslash inhibited, we keep the quote state as-is and
 * return early.
 */

void	check_quotes(char c, t_tokenizer *tokenizer)
{
	if (c == '$')
		tokenizer->dollar = true;
	if (tokenizer->backslash_inhibited
		&& ((tokenizer->in_quotes && tokenizer->quote_type != '\'')
			|| !tokenizer->in_quotes))
		return ;
	if ((c == '\'' || c == '\"') && !(tokenizer->in_quotes))
	{
		tokenizer->in_quotes = true;
		tokenizer->quote_type = c;
		if (tokenizer->quote_type == '\'')
			tokenizer->in_squotes = true;
	}
	else if (c == tokenizer->quote_type && tokenizer->in_quotes)
	{
		tokenizer->in_quotes = false;
		if (tokenizer->quote_type == '\'')
			tokenizer->in_squotes = false;
	}
	else if (c == '\'')
	{
			if (tokenizer->in_squotes)
				tokenizer->in_squotes = false;
			else
				tokenizer->in_squotes = true;
	}
	else if (c == '{' && tokenizer->dollar)
	{
		if (!(tokenizer->in_quotes))
		{
			tokenizer->in_braces = true;
			(tokenizer->brace_count)++;
		}
		else if (tokenizer->in_quotes && tokenizer->quote_type == '\'')
		{
			tokenizer->in_squote_braces = true;
			(tokenizer->brace_sq_count)++;
		}
		else if (tokenizer->in_quotes && tokenizer->quote_type == '\"')
		{
			tokenizer->in_dquote_braces = true;
			(tokenizer->brace_dq_count)++;
		}
	}
	else if (c == '}')
	{
		if (!(tokenizer->in_quotes))
		{
			if (tokenizer->brace_count > 0)
				(tokenizer->brace_count)--;
			if (tokenizer->brace_count == 0)
				tokenizer->in_braces = false;
		}
		else if (tokenizer->in_quotes && tokenizer->quote_type == '\'')
		{
			if (tokenizer->brace_sq_count > 0)
				(tokenizer->brace_sq_count)--;
			if (tokenizer->brace_sq_count == 0)
				tokenizer->in_squote_braces = false;
		}
		else if (tokenizer->in_quotes && tokenizer->quote_type == '\"'
				&& !(tokenizer->in_squotes))
		{
			if (tokenizer->brace_dq_count > 0)
				(tokenizer->brace_dq_count)--;
			if (tokenizer->brace_dq_count == 0)
				tokenizer->in_dquote_braces = false;
		}
	}
	if (c != '$' && tokenizer->dollar)
		tokenizer->dollar = false;
}
