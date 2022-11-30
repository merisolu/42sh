/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:17:26 by amann             #+#    #+#             */
/*   Updated: 2022/11/30 14:12:10 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*
 * POSIX standard: https://pubs.opengroup.org/onlinepubs/9699919799/
 * NB: no option flags required to meet the standard.
 *
 * Description: "The type utility shall indicate how each argument would be
 * interpreted if used as a command name."
 *
 * Type will cycle through the args given and confirm if they are:
 *	-	a shell builtin
 *	-	an executable in the PATH
 *	-	an alias
 *	-	a function
 *	-	a keyword (reserved word)
 *
 * As aliasing, reserved words and functions have not been implemented, we
 * just handle builtins and executables for now, and an error message if
 * no result was found.
 */

static void	print_type_res(char const *name, char const *msg)
{
	ft_printf("%s is %s\n", name, msg);
}

static void	print_type_err(char const *name, char const *msg)
{
	ft_dprintf(STDERR_FILENO, "21sh: type: %s: %s\n", name, msg);
}

static void	search_bins(char const *name, int *res, t_state *state)
{
	char	*path;

	path = NULL;
	bin_env_find(name, state->env, &path);
	if (path)
	{
		print_type_res(name, path);
		ft_strdel(&path);
		*res = 0;
	}
	else
		print_type_err(name, TYPE_NOT_FOUND);
}

int	cmd_type(char *const *args, t_state *state)
{
	size_t	i;
	int		res;
	char	*path;

	res = 1;
	i = 1;
	while (args[i])
	{
		path = built_in_search(args[i]);
		if (path)
		{
			print_type_res(args[i], TYPE_IS_BUILTIN);
			ft_strdel(&path);
			res = 0;
		}
		else
			search_bins(args[i], &res, state);
		i++;
	}
	return (res);
}
