/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:14:18 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/05 14:26:25 by jumanner         ###   ########.fr       */
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
	if (tokenizer->backslash_inhibited
		&& ((tokenizer->in_quotes && tokenizer->quote_type != '\'')
			|| !tokenizer->in_quotes))
		return ;
	if ((c == '\'' || c == '\"') && !(tokenizer->in_quotes))
	{
		tokenizer->in_quotes = true;
		tokenizer->quote_type = c;
	}
	else if (c == tokenizer->quote_type && tokenizer->in_quotes)
		tokenizer->in_quotes = false;
}
