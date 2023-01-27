/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:23:36 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 13:23:51 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	start_editor(char *editor, t_state *state)
{
	char		*path;
	pid_t		fork_result;
	static char	*args[3] = {
		"",
		FC_EDIT_FILE,
		NULL
	};

	args[0] = editor;
	find_binary(editor, state, &path, true);
	if (path == NULL)
		return (print_error_bool(
				false, ERRTEMPLATE_NAMED, "fc", "no command found"));
	fork_result = fork();
	if (fork_result == -1)
		return (print_error_bool(
				false, ERRTEMPLATE_NAMED, "fc", ERR_CHILD_PROC_FAIL));
	if (fork_result != 0)
	{
		free(path);
		waitpid(fork_result, NULL, 0);
		return (true);
	}
	if (execve(path, args, state->env) == -1)
		exit(print_error(1, ERRTEMPLATE_NAMED, "fc", ERR_CHILD_PROC_FAIL));
	return (true);
}

bool	cmd_fc_history_edit(char *editor, t_fc_range *range, t_state *state)
{
	return (cmd_fc_write_commands_to_file(range, state)
		&& start_editor(editor, state) && cmd_fc_read_command_from_file(state));
}
