/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_retokenize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:21:06 by amann             #+#    #+#             */
/*   Updated: 2023/10/10 16:12:14 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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
	{'\\', TOKEN_BACKSLASH},
	{'=', TOKEN_EQUALS},
	{'#', TOKEN_HASH},
	{'%', TOKEN_PERCENT},
	{'?', TOKEN_QUESTION_MARK},
	{'*', TOKEN_STAR},
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
	if (ft_isalnum(value) || value == '_')
		return (TOKEN_WORD);
	else
		return (TOKEN_JUNK);
}

static void	add_token_and_reset_buff(t_token **result, t_retokenize *t)
{
	token_add(result, t->previous_type, ft_strdup(t->buff));
	ft_strclr(t->buff);
	t->j = 0;
}

static void retokenize_init(t_retokenize *t, char *word)
{
	ft_bzero((void *)t, sizeof(t_retokenize));
	t->buff = ft_strnew(ft_strlen(word) + 1);
	t->previous_type = get_parser_token_type(word[0]);
	(t->buff)[0] = word[0];
	t->i = 1;
	t->j = 1;
}

/*
 * Separating tokenisation process from the backslash and quote inhibition
 * process.
 * This function simply takes the given 'word', from the AST, and creates
 * a like-for-like list of tokens.
 * Inhibition handling is now completed in a subsequent process, for the
 * sake of simplicity. The previous combined algorithm was extremely 
 * convoluted.
 */
t_token	*expansions_retokenize(char *word)
{
	t_token			*result;
	t_retokenize	t;

	ft_printf("word = %s\n", word);

	result = NULL;
	retokenize_init(&t, word);
	if (!t.buff)
		return (NULL);
	while (word[t.i])
	{
		t.current_type = get_parser_token_type(word[t.i]);
		if (t.current_type != t.previous_type)
		{
			add_token_and_reset_buff(&result, &t);
			t.previous_type = t.current_type;
		}
		t.buff[t.j] = word[t.i];
		(t.j)++;
		(t.i)++;
	}
	add_token_and_reset_buff(&result, &t);
	free(t.buff);

	print_tokens(result);

	return (result);
}
