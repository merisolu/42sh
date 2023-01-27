/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fc_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:23:36 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/27 11:52:05 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static bool	write_command_to_fd(int fd, int history_index, t_state *state)
{
	int	write_result;

	write_result = write(fd, state->history[history_index],
			ft_strlen(state->history[history_index]));
	if (write_result == -1)
		return (false);
	write_result = write(fd, "\n", 1);
	return (write_result != -1);
}

static bool	write_commands_to_file(t_fc_range *range, t_state *state)
{
	int		fd;
	bool	write_successful;
	int		i;

	fd = open(FC_EDIT_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (print_error_bool(
				false, ERRTEMPLATE_NAMED, "fc", ERR_OPEN_FAIL));
	i = range->start;
	while (1)
	{
		write_successful = write_command_to_fd(
				fd, cmd_fc_range_number_to_index(i, state), state);
		if (!write_successful || i == range->end)
			break ;
		if (range->start > range->end)
			i--;
		else
			i++;
	}
	close(fd);
	if (!write_successful)
		print_error(0, ERRTEMPLATE_NAMED, "fc", ERR_WRITE_FAIL);
	return (write_successful);
}

// TODO: Read multiple commands.
static bool	read_command_from_file(t_state *state)
{
	int		fd;
	int		read_return;
	char	*last_newline;

	ft_bzero(state->history[1], INPUT_MAX_SIZE);
	fd = open(FC_EDIT_FILE, O_RDONLY);
	if (fd == -1)
		return (print_error_bool(
				false, ERRTEMPLATE_NAMED, "fc", ERR_OPEN_FAIL));
	read_return = read(fd, state->history[1], INPUT_MAX_SIZE);
	if (read_return == -1)
		return (print_error_bool(false, ERRTEMPLATE_NAMED "fc", ERR_READ_FAIL));
	last_newline = ft_strrchr(state->history[1], '\n');
	if (last_newline)
		*last_newline = '\0';
	return (true);
}

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
		waitpid(fork_result, NULL, 0);
		return (true);
	}
	if (execve(path, args, state->env) == -1)
		exit(print_error(1, ERRTEMPLATE_NAMED, "fc", ERR_CHILD_PROC_FAIL));
	return (true);
}

bool	cmd_fc_history_edit(char *editor, t_fc_range *range, t_state *state)
{
	return (write_commands_to_file(range, state)
		&& start_editor(editor, state) && read_command_from_file(state));
}
