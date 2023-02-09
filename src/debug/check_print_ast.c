/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_print_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:06:54 by amann             #+#    #+#             */
/*   Updated: 2023/02/09 15:01:22 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	create_print_file(t_ast **ast_list)
{
	int	fd;
	int	permissions;

	permissions = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH;
	fd = open(TMP_FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, permissions);
	if (fd == -1)
		return ;
	print_ast(ast_list, fd);
	close(fd);
	return ;
}

static void	display_print_file(void)
{
	char	*line;
	int		fd;

	fd = open(TMP_FILE_PATH, O_RDONLY);
	if (fd == -1)
		return ;
	while (ft_get_next_line(fd, &line) > 0)
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
	close(fd);
}

void	check_print_ast(t_ast **ast_list, t_state *state, bool exp)
{
	char	*val;

	val = env_get("AST", state->env);
	if (!val)
		return ;
	if (ft_strequ(val, "0") && !exp)
	{
		create_print_file(ast_list);
		return ;
	}
	if (ft_strequ(val, "1") && exp)
	{
		print_ast(ast_list, STDOUT_FILENO);
		return ;
	}
	if (ft_strequ(val, "0") && exp)
	{
		display_print_file();
		return ;
	}
	return ;
}
