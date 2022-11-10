/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:29:22 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/09 15:46:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	handle_delete_char(t_input_context *ctx)
{
	if (ctx->cursor == 0)
		return (0);
	ft_strcpy(ctx->input + ctx->cursor - 1, ctx->input + ctx->cursor);
	ft_bzero(ctx->input + ft_strlen(ctx->input),
		INPUT_MAX_SIZE - ft_strlen(ctx->input));
	ctx->cursor--;
	return (1);
}

static t_key_handler_dispatch	*get_dispatch_table(void)
{
	static const t_key_handler_dispatch	dispatch_table[] = {
	{BACKSPACE, &handle_delete_char},
	{ARROW_LEFT, &handle_left},
	{ARROW_RIGHT, &handle_right},
	{HOME_KEY, &handle_home},
	{END_KEY, &handle_end},
	{ARROW_UP_ALT, &handle_alt_up},
	{ARROW_DOWN_ALT, &handle_alt_down},
	{ARROW_LEFT_ALT, &handle_alt_left},
	{ARROW_RIGHT_ALT, &handle_alt_right},
	{CTRL_D, &ctrl_d},
	{CTRL_K, &cut_from_cursor},
	{CTRL_U, &cut_to_cursor},
	{CTRL_W, &cut_word},
	{CTRL_Y, &paste},
	{0, NULL}
	};

	return ((t_key_handler_dispatch *)dispatch_table);
}

// TODO: Missing
	// {TAB, &autocomplete},
	// {ARROW_UP, &handle_history},
	// {ARROW_DOWN, &handle_history},
int	handle_key(char *buffer, t_input_context *ctx)
{
	size_t					i;
	int						command_result;
	t_key_handler_dispatch	*dispatch_table;

	dispatch_table = get_dispatch_table();
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strnequ(dispatch_table[i].activator, buffer,
				ft_strlen(dispatch_table[i].activator)))
		{
			command_result = dispatch_table[i].run(ctx);
			if (command_result > 0)
				return (ft_strlen(dispatch_table[i].activator));
			else if (command_result < 0)
				return (command_result);
			return (0);
		}
		i++;
	}
	return (0);
}
