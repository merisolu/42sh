/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/11 13:54:47 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

/* Includes */

# include "utils.h"
# include "hash.h"
# include "environment.h"

/* Macros for type */

# define TYPE_IS_BUILTIN "a shell builtin"
# define TYPE_NOT_FOUND "not found"

/* Types */

typedef void	t_arg_parse_error(char c);

typedef int		t_cmd(char *const *args, t_state *state);

typedef struct s_cmd_dispatch
{
	const char	*name;
	t_cmd		*run;
}	t_cmd_dispatch;

typedef struct s_cmd_env
{
	char	flags[1];
	char	**args;
	char	**env;
}	t_cmd_env;

/* Files */

/* built_ins.c */
const t_cmd_dispatch	*get_built_in_dispatch(void);
t_cmd					*built_in_get(const char *name);
char					*built_in_search(const char *partial_name);
pid_t					built_in_run(t_cmd cmd, char *const *args, t_state *state, \
					t_ast_context *ast);

/* built_ins_flags.c */
int						parse_flags(char *const *args, char *valid, char *found, \
					t_arg_parse_error *on_error);

/* cmd_echo.c */
int						cmd_echo(char *const *args, t_state *state);

/* cmd_cd.c */
int						cmd_cd(char *const *args, t_state *state);

/* cmd_export.c */
int						cmd_export(char *const *args, t_state *state);

/* export_set.c */
int						export_set(const char *name, const char *value, char *const **env);

/* cmd_hash.c */
int						cmd_hash(char *const *args, t_state *state);

/* cmd_fc.c */
int						cmd_fc(char *const *args, t_state *state);

/* cmd_exit.c */
int						cmd_exit(char *const *args, t_state *state);

/* cmd_execute_script.c */
int						cmd_execute_script(char *const *args, t_state *state);

/* cmd_set.c */
int						cmd_set(char *const *args, t_state *state);

/* cmd_true_false.c */
int						cmd_true(char *const *args, t_state *state);
int						cmd_false(char *const *args, t_state *state);

/* cmd_type.c */
int						cmd_type(char *const *args, t_state *state);

/* cmd_unset.c */
int						cmd_unset(char *const *args, t_state *state);

/* delete_var.c */
void					delete_var(char *name, char *const **arr);
bool					exported_no_equals(char *name, t_state *state);

/* print_exported.c */
bool					print_exported(char *const *args, t_state *state);
#endif
