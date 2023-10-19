/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inhibitors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:03:49 by jumanner          #+#    #+#             */
/*   Updated: 2023/10/19 15:58:12 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	handle_quote_state(t_token **list, bool *in_dq, bool *in_sq)
{
	int	type;

	type = (*list)->type;
	if (type == TOKEN_SINGLE_QUOTE && (*in_dq == false || *in_sq == true))
	{
		*in_sq = !(*in_sq);
		*list = (*list)->next;
		return ;
	}
	if (type == TOKEN_DOUBLE_QUOTE && (*in_sq == false || *in_dq == true))
	{
		*in_dq = !(*in_dq);
		*list = (*list)->next;
		return ;
	}
	return ;
}

static void	handle_backslash(t_token **list, bool in_quotes, t_token **head)
{
	t_token	*current;

	if (in_quotes && !((*list)->next->type & (TOKEN_DOLLAR | \
		TOKEN_DOUBLE_QUOTE | TOKEN_BACKSLASH | TOKEN_NEWLINE)))
		(*list)->type = TOKEN_WORD;
	else if ((*list)->next)
	{
		current = *list;
		(*list)->next->type = TOKEN_WORD;
		if ((*list)->previous)
			(*list)->previous->next = (*list)->next;
		else
			*head = (*list)->next;
		(*list)->next->previous = (*list)->previous;
		*list = (*list)->next;
		token_free(&current);
	}
	return ;
}

static void	quote_inhib(t_token **list, bool in_sq, bool in_dq, t_token **head)
{
	if (in_sq && (*list)->type != TOKEN_SINGLE_QUOTE)
		(*list)->type = TOKEN_WORD;
	else if (in_dq && (*list)->type != TOKEN_DOUBLE_QUOTE)
	{
		if ((*list)->type == TOKEN_BACKSLASH)
			handle_backslash(list, true, head);
		else if ((*list)->type != TOKEN_DOLLAR)
			(*list)->type = TOKEN_WORD;
	}
	return ;
}

/*
 * quote and backslash handling should happen before the expansions_loop
 * un-closed quotes are checked by input process to handle newlines.
 * Therefore, it should be safe to re-categorise tokens inside quotes
 * based on the quote type
 *
 * With backslash, it should be ok to just change the type of the
 * subsequent token - thereby 'escaping' it before the expansions_loop
 *
 * Regarding quotes:
 *
 * https://www.gnu.org/software/bash/manual/html_node/Single-Quotes.html
 * Single quotes are nice and simple, every character in-between is interpreted
 * using its literal value, any special character loses its meaning.
 *
 * https://www.gnu.org/software/bash/manual/html_node/Double-Quotes.html
 * Double quotes are a more 'soft' inhibit, the following special chars retain
 * their meaning:
 *		'$' (dollar), '!' (exclamation mark), and '`' (back-tick)
 *
 * '\' (backslash) will retain its meaning only when followed by:
 * 		'$' (dollar), '`' (back-tick), '"' (double-quote), '\' (backslash),
 * 		'\n' (new-line)
 * So will be removed under those circumstances. But everything else is
 * interpreted literally.
 */
void	handle_inhibitors(t_token **list)
{
	t_token	*head;
	bool	in_dquotes;
	bool	in_squotes;

	head = *list;
	in_dquotes = false;
	in_squotes = false;
	while (*list)
	{
		if ((*list)->type & (TOKEN_SINGLE_QUOTE | TOKEN_DOUBLE_QUOTE))
			handle_quote_state(list, &in_dquotes, &in_squotes);
		if (!(*list))
			break ;
		if (in_squotes || in_dquotes)
			quote_inhib(list, in_squotes, in_dquotes, &head);
		if (!in_squotes && !in_dquotes && (*list)->type == TOKEN_BACKSLASH)
			handle_backslash(list, false, &head);
		if (*list)
			*list = (*list)->next;
	}
	*list = head;
	return ;
}
