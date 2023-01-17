/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:18:43 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/17 15:45:32 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static const t_cmd_dispatch	*get_dispatch(void)
{
	static const t_cmd_dispatch	dispatch_table[] = {
	{"cd", &cmd_cd},
	{"echo", &cmd_echo},
	{"export", &cmd_export},
	{"fc", &cmd_fc},
	{"unset", &cmd_unset},
	{"hash", &cmd_hash},
	{"jobs", &cmd_jobs},
	{"fg", &cmd_fg},
	{"bg", &cmd_bg},
	{"true", &cmd_true},
	{"false", &cmd_false},
	{"type", &cmd_type},
	{"set", &cmd_set},
	{"exit", &cmd_exit},
	{"", NULL}
	};

	return (&(dispatch_table[0]));
}

char	*built_in_search(const char *partial_name)
{
	const t_cmd_dispatch	*dispatch_table;
	size_t					i;

	dispatch_table = get_dispatch();
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strequ(
				partial_name, dispatch_table[i].name))
			return (ft_strdup((char *)dispatch_table[i].name));
		i++;
	}
	return (NULL);
}

static bool	check_magic_num(const char *name)
{
	char	magic[6];
	int		fd;
	int		ret;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (false);
	ft_bzero(magic, 6);
	ret = read(fd, magic, 5);
	if (ret == -1)
		return (false);
	close(fd);
	if (ft_strequ(magic, MAGIC_NUMBER))
		return (true);
	return (false);
}

t_cmd	*built_in_get(const char *name)
{
	const t_cmd_dispatch	*dispatch_table;
	size_t					i;

	if (ft_strnequ(name, "./", 2) && check_magic_num(name + 2))
		return (&cmd_execute_script);
	dispatch_table = get_dispatch();
	i = 0;
	while (dispatch_table[i].run != NULL)
	{
		if (ft_strequ(dispatch_table[i].name, name))
			return (dispatch_table[i].run);
		i++;
	}
	return (NULL);
}

int	built_in_run(t_cmd cmd, char *const *args, t_state *state, \
	t_ast_context *ast)
{
	if (!env_set("_", args[0], &(state->env)))
		set_return_value(1, state);
	else if (ast->node->right
		&& !handle_redirects(ast->node->right, ast->redirect))
		set_return_value(1, state);
	else
		set_return_value(cmd(args, state), state);
	return (state->last_return_value);
}
