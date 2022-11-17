/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:56:40 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/17 16:00:10 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	free_env_args(t_cmd_env *env_args, int return_value)
{
	ft_free_null_array((void **)(env_args->args));
	ft_free_null_array((void **)(env_args->env));
	return (return_value);
}

static void	on_invalid_argument(char c)
{
	ft_dprintf(STDERR_FILENO, "illegal option -- %c \nusage: env [-i]", c);
	ft_putstr_fd("[name=value ...] [utility [argument ...]]\n", STDERR_FILENO);
}

static int	print_env_error(char *str1, char *str2, char *str3, int value)
{
	ft_dprintf(STDERR_FILENO, "env: %s%s%s\n", str1, str2, str3);
	return (value);
}

static int	args_to_env(char *const *args, char *const *env, int *index, \
t_cmd_env *cmd)
{
	char	*pair;
	char	*temp;

	if (ft_strchr(cmd->flags, 'i'))
	{
		cmd->env = (char **)ft_memalloc(sizeof(char *));
		if (!cmd->env)
			return (print_named_error("env", ERR_MALLOC_FAIL, -1));
	}
	else if (!ft_dup_null_array((void **)env, (void ***)&(cmd->env), var_copy))
		return (print_named_error("env", ERR_MALLOC_FAIL, -1));
	while (args[*index] && ft_strchr(args[*index], '='))
	{
		pair = args[*index];
		temp = ft_strchr(pair, '=') + 1;
		pair[ft_dstchr(pair, '=', ft_strlen(pair))] = '\0';
		if (!env_set(pair, temp, (char *const **)&(cmd->env)))
			return (free_env_args(cmd, -1));
		(*index)++;
	}
	return (0);
}

int	cmd_env(char *const *args, t_state *state)
{
	t_cmd_env	cmd;
	int			i;
	char		*path;
	int			return_value;

	ft_bzero(&cmd, sizeof(t_cmd_env));
	i = parse_flags(args + 1, "i", cmd.flags, &on_invalid_argument) + 1;
	if (args_to_env(args, state->env, &i, &cmd) == -1)
		return (-1);
	if (i <= 0)
		return (free_env_args(&cmd, 1));
	if (!args[i])
	{
		env_print_all(cmd.env);
		return (free_env_args(&cmd, 0));
	}
	if (!ft_dup_null_array((void **)args + i, (void ***)&(cmd.args), var_copy))
		return (
			print_named_error("env", ERR_MALLOC_FAIL, free_env_args(&cmd, 1)));
	if (bin_env_find(args[i], state->env, &path) == 0)
		return (print_env_error(args[i], ": ", ERR_NO_SUCH_FILE_OR_DIR,
				free_env_args(&cmd, 1)));
	return_value = bin_execute(path, cmd.args, cmd.env, NULL);
	free(path);
	return (free_env_args(&cmd, return_value));
}
