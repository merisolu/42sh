/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_display_control.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:02:48 by amann             #+#    #+#             */
/*   Updated: 2023/03/26 17:10:55 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static bool	autocomplete_display_warning(t_state *state, size_t len)
{
	char	buffer[BUF_SIZE + 1];
	size_t	orig_cursor;

	cursor_to_end(&(state->input_context), &orig_cursor);
	ft_bzero(&buffer, BUF_SIZE + 1);
	ft_dprintf(STDOUT_FILENO, "Display all %d possibilities? (y or n) ", len);
	while (1)
	{
		if (read(STDIN_FILENO, buffer, BUF_SIZE) == -1)
			return (print_error_bool(false, "error: %s\n", ERR_READ_FAIL));
		if (ft_strchr(buffer, 'y'))
			break ;
		if (ft_strchr(buffer, 'n') || g_last_signal == SIGINT)
		{
			ft_putendl("");
			if (g_last_signal == SIGINT)
				g_last_signal = 0;
			cursor_to_orig(&(state->input_context), orig_cursor);
			return (false);
		}
	}
	cursor_to_orig(&(state->input_context), orig_cursor);
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
 * wrap_up().
 *
 * If there are a lot of possibilities, we prompt the user with a warning
 * before dumping loads of text on to the STDOUT. The default min in bash
 * for this warning to be given is 100 (completion-query-items):
 *
 * https://www.gnu.org/software/bash/manual/bash.html#Readline-Init-File-Syntax
 *
*/

static void	append_space(t_input_context *ctx, char **text, bool filtered)
{
	char	*temp;

	if (ctx->input[ctx->cursor] || filtered
		|| (*text)[ft_strlen(*text) - 1] == '/')
		return ;
	temp = ft_strnew(sizeof(char) * (ft_strlen(*text) + 1));
	if (!temp)
		return ;
	ft_strcpy(temp, *text);
	temp[ft_strlen(*text)] = ' ';
	free(*text);
	*text = temp;
}

static int	insert_text(t_input_context *ctx, char **text, bool filtered)
{
	int		limit_reached;
	char	*crs_start;
	size_t	new_cursor_pos;
	size_t	text_len;

	append_space(ctx, text, filtered);
	text_len = ft_strlen(*text);
	new_cursor_pos = ctx->cursor + text_len;
	limit_reached = ft_strlen(ctx->input) + text_len >= INPUT_MAX_SIZE;
	if (limit_reached)
	{
		(*text)[INPUT_MAX_SIZE - ft_strlen(ctx->input)] = '\0';
		text_len = ft_strlen(*text);
		new_cursor_pos = ctx->cursor + text_len;
	}
	crs_start = ctx->input + ctx->cursor;
	ft_memmove(crs_start + text_len, crs_start, ft_strlen(crs_start));
	ft_memcpy(crs_start, *text, text_len);
	ctx->cursor = new_cursor_pos;
	if (limit_reached)
		ft_putstr(tgetstr("bl", NULL));
	return (1);
}

int	autocomplete_display_control(t_auto *autocomp, t_state *state)
{
	size_t			len;

	len = ft_null_array_len((void **)(autocomp->search_result));
	if (len == 1)
		return (insert_text(
				&(state->input_context),
				&(autocomp->search_result[0]),
				autocomp->auto_bools.filtered
				));
	else if (len)
	{
		len = ft_null_array_len((void **)(autocomp->search_result));
		if (len > AUTOCOMP_DISPLAY_LIMIT
			&& !autocomplete_display_warning(state, len))
			return (0);
		autocomplete_display_columns(autocomp->search_result, len, state);
	}
	return (-1);
}
