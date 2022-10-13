/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:13:35 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/13 15:01:01 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	g_last_signal;

static int	get_state_struct(char *const **env, t_state *result)
{
	size_t	i;

	i = 0;
	ft_bzero(result, sizeof(t_state));
	result->input = ft_memalloc(INPUT_MAX_SIZE + 1);
	if (!result->input)
		return (0);
	result->clipboard = ft_memalloc(INPUT_MAX_SIZE + 1);
	if (!result->clipboard)
		return (0);
	while (i < HISTORY_SIZE)
	{
		result->history[i] = ft_memalloc(INPUT_MAX_SIZE + 1);
		if (!result->history[i])
			return (0);
		i++;
	}
	if (!ft_dup_null_array((void **)*env, (void ***)&(result->env), var_copy))
		return (0);
	return (
		env_unset("OLDPWD", &(result->env))
	);
}
/*
 * check start == pipe_sequence node
 * check if right node is null (if not, we need to pipe something...)
 * check if left node contains a simple command (if not... bad things... exit)
 * move to command node.
 * check if right node is null (if not, we have to handle a redirection)
 * check if left node is command_args node
 * return a pointer to the arg_list from that node to the args variable
 *
 */

int	check_node_type(t_ast *node, t_ast_node_type type)
{
	if (node && node->node_type == type)
		return (TRUE);
	return (FALSE);
}

int	get_args_from_tree(t_ast *tree, char ***args)
{
	t_ast	*cmd_node;

	if (!check_node_type(tree, AST_PIPE_SEQUENCE))
		return (0);
	if (tree->right)
		return (0); //TODO handle piping
	if (!tree->left || !check_node_type(tree->left, AST_SIMPLE_COMMAND))
		return (0);
	cmd_node = tree->left;
	if (cmd_node->right)
		return (0); //TODO handle redirects
	if (!cmd_node->left || !check_node_type(cmd_node->left, AST_COMMAND_ARGS))
		return (0);
	*args = cmd_node->left->arg_list;
	return (1);
}

static void	tokenize_and_execute(t_state *state)
{
	t_ast	**tree;
	char	**args;
	int		i;

	if (ft_strisempty(state->input))
	{
		clear_input(state, 1);
		return ;
	}
	if (!set_orig_config(state))
	{
		print_error(ERR_TERMIOS_FAIL, 1);
		return ;
	}
	history_store(state->input, state);
	state->cursor = ft_strlen(state->input);
	state->previous_input_length = 0;
	ft_putchar('\n');

	//The parser now builds a beautiful AST
	//It no longer expands variables or handles quotes properly
	tree = parse(tokenize(state->input), state);

	args = NULL;
	i = 0;
	while (get_args_from_tree(tree[i], &args))
	{
		set_return_value(execute(args, state), state);
		if (args)
			env_set("_", args[ft_null_array_len((void **)args) - 1], &(state->env));
		i++;
	}

	//TODO build a function to free the tree
//	ft_free_null_array((void **)args);
	clear_input(state, 0);
	if (!set_input_config(state))
		print_error(ERR_TERMIOS_FAIL, 1);
}

static int	setup(char *const **env, t_state *state)
{
	char	*term;
	int		database_result;

	term = getenv("TERM");
	if (!term)
		return (print_error(ERR_ENV_MISSING_TERM, 0));
	database_result = tgetent(NULL, term);
	if (database_result < 0)
		return (print_error(ERR_TERMCAP_NO_ACCESS, 0));
	else if (database_result == 0)
		return (print_error(ERR_TERMCAP_NO_ENTRY, 0));
	if (!get_state_struct(env, state))
		return (print_error(ERR_MALLOC_FAIL, 0));
	if (!configure_input(state))
		return (print_error(ERR_TERMIOS_FAIL, 0));
	if (!set_shlvl(&(state->env)))
		return (0);
	set_signal_handling();
	save_cursor(state);
	print_state(state);
	return (1);
}

static int	cleanup(t_state *state)
{
	if (!set_orig_config(state))
		return (print_error(ERR_TERMIOS_FAIL, 1));
	ft_free_array_elements((void **)state->history, HISTORY_SIZE);
	ft_free_null_array((void **)(state->env));
	free(state->input);
	free(state->clipboard);
	return (state->exit_return_value);
}

int	main(const int argc, const char **argv, char *const *env)
{
	t_state		state;

	(void)argc;
	(void)argv;
	if (!setup(&env, &state))
		return (1);
	while (!state.exiting)
	{
		check_signal(&state);
		if (get_input(&state) == INPUT_NEWLINE_FOUND)
		{
			tokenize_and_execute(&state);
			if (!state.exiting)
			{
				if (g_last_signal != 0 && state.last_return_value > 128)
					ft_putchar('\n');
				save_cursor(&state);
				print_state(&state);
			}
			g_last_signal = 0;
		}
	}
	ft_putendl("exit");
	return (cleanup(&state));
}
