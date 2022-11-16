/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_print_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:06:54 by amann             #+#    #+#             */
/*   Updated: 2022/11/16 17:28:07 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	create_print_file(t_ast **ast_list)
{
	int	fd;
	int	permissions;

	permissions = S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH;
	fd = open(TMP_FILE_PATH, O_RDWR | O_CREAT, permissions);
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
	{
		remove(TMP_FILE_PATH);
		return ;
	}
	while (ft_get_next_line(fd, &line))
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
	close(fd);
	remove(TMP_FILE_PATH);
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
