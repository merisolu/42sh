/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:21:45 by amann             #+#    #+#             */
/*   Updated: 2022/10/20 15:16:51 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <fcntl.h>

int	cmd_redir_test(char *const *args, t_state *state)
{
	(void) args;
	(void) state;

	char	*filename2 = "test_in";
	char	*filename = "test_out";
	char	buff[20];
	int		fd_out;
	int		fd_in;
	int		saved_out;
	int		saved_in;

	ft_bzero(buff, 20);
	//O_APPEND flag needed in event of >>
	//With output, we need to create the file if it doesnt exist, and apply appropriate permissions
	//When redirecting input we only need read permissions
	fd_out = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH);
	fd_in = open(filename2, O_RDONLY);
	if (fd_out == -1 || fd_in == -1)
		return (1);

	//STDIN and STDOUT need to be saved into temporary vars
	saved_out = dup(STDOUT_FILENO);
	saved_in = dup(STDIN_FILENO);
	if (saved_out == -1 || saved_in == -1)
		return (1);

	//STDIN and STDOUT are redirected to the specified files
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (1);

	//The fd's opened for the redirection are then closed, they are no longer needed
	close(fd_out);
	close(fd_in);

	read(STDIN_FILENO, buff, ft_strlen("well hello...") + 1);
	write(STDOUT_FILENO, buff, ft_strlen("well hello...") + 1);
	//we now execute our command
	//execve();
	//ft_putendl("well hello ...");

	//STDIN and STDOUT are reset using the temp vars
	if (dup2(saved_out, STDOUT_FILENO) == -1)
		return (1);
	if (dup2(saved_in, STDIN_FILENO) == -1)
		return (1);

	return (0);
}
