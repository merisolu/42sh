/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_display_control.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:02:48 by amann             #+#    #+#             */
/*   Updated: 2023/01/17 15:14:54 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

bool	autocomplete_display_warning(t_state *state, size_t len)
{
	char	buffer[BUF_SIZE + 1];

	ft_bzero(&buffer, BUF_SIZE + 1);
	ft_dprintf(
		STDOUT_FILENO,
		"\nDisplay all %d possibilities? (y or n) ",
		len);
	while (1)
	{
		read(STDIN_FILENO, buffer, BUF_SIZE);
		if (ft_strchr(buffer, 'y'))
			break ;
		if (ft_strchr(buffer, 'n') || g_last_signal == SIGINT)
		{
			ft_putendl("");
			if (g_last_signal == SIGINT)
				g_last_signal = 0;
			save_cursor(&(state->input_context));
			return (false);
		}
	}
	return (true);
}

/*
 * This function controls how the result is displayed. If we only have one
 * possible completion, we can append to the cursor position the remaining
 * text in that option.
 *
 * In all other cases, we need to present the user with all the possible
 * things it could be. They are displayed in lexicographical order and
 * in nice neat columns, with no duplicates. The sorting is handled in
 * wrap_up.
 *
 * If there are a lot of possibilities, with prompt the user with a warning
 * before dumping loads of text on to the STDOUT. The default min in bash
 * for this warning to be given is 100 (completion-query-items):
 *
 * https://www.gnu.org/software/bash/manual/bash.html#Readline-Init-File-Syntax
 *
 */

static void	append_space(char **text)
{
	char	*temp;

	temp = ft_strnew(sizeof(char) * (ft_strlen(*text) + 1));
	if (!temp)
		return ;
	ft_strcpy(temp, *text);
	temp[ft_strlen(*text)] = ' ';
	free(*text);
	*text = temp;
}

static bool	insert_text(t_input_context *ctx, char **text, bool filtered)
{
	int		limit_reached;
	size_t	new_cursor_pos;
	size_t	text_len;

	if (!(ctx->input[ctx->cursor]) && !filtered
		&& (*text)[ft_strlen(*text) - 1] != '/')
		append_space(text);
	text_len = ft_strlen(*text);
	new_cursor_pos = ctx->cursor + text_len;
	limit_reached = ft_strlen(ctx->input) + text_len >= INPUT_MAX_SIZE;
	if (limit_reached)
	{
		(*text)[INPUT_MAX_SIZE - ft_strlen(ctx->input)] = '\0';
		text_len = ft_strlen(*text);
		new_cursor_pos = ctx->cursor + text_len;
	}
	ft_memmove(
		ctx->input + ctx->cursor + text_len,
		ctx->input + ctx->cursor,
		ft_strlen(ctx->input + ctx->cursor));
	ft_memcpy(ctx->input + ctx->cursor, *text, text_len);
	ctx->cursor = new_cursor_pos;
	if (limit_reached)
		ft_putstr(tgetstr("bl", NULL));
	return (true);
}

bool	autocomplete_display_control(t_state *state, char ***search_result, \
		bool filtered)
{
	size_t			len;

	len = ft_null_array_len((void **)(*search_result));
	if (len == 1)
		return (insert_text(&(state->input_context), &((*search_result)[0]), \
				filtered));
	else if (len)
	{
		len = ft_null_array_len((void **)(*search_result));
		if (len > 100 && !autocomplete_display_warning(state, len))
		{
			ft_free_null_array((void **)*search_result);
			return (false);
		}
		autocomplete_display_columns(*search_result, len, state);
	}
	return (true);
}
