/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/22 10:26:12 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

/* Includes */

# include <signal.h>
# include "utils.h"
# include "hash.h"
# include "environment.h"

/* Macros for type */

# define TYPE_IS_BUILTIN "a shell builtin"
# define TYPE_NOT_FOUND "not found"

/* Constants */

# define CD_USAGE "cd: usage: cd [-L|-P] [dir]"
# define FC_EDIT_FILE "/tmp/42sh_fc_edit_file"
# define FC_USAGE "fc: usage: fc [-nlr] [-e ename] [first [last]] \
or fc -s [old=new] [first]\n"
# define FC_MAX_REPLACE INPUT_MAX_SIZE

/* Types */

typedef void	t_arg_parse_error(char c);

typedef int		t_cmd(char *const *args, t_state *state);

typedef struct s_cmd_dispatch
{
	const char	*name;
	t_cmd		*run;
}	t_cmd_dispatch;

typedef struct s_fc_range
{
	int	start;
	int	end;
}	t_fc_range;

/* Files */

/* built_ins.c */
const t_cmd_dispatch	*get_built_in_dispatch(void);
t_cmd					*built_in_get(const char *name);
char					*built_in_search(const char *partial_name);
int						built_in_run(t_cmd cmd, char *const *args, \
						t_state *state, t_ast_context *ast);

/* built_ins_flags.c */
int						parse_flags(char *const *args, char *valid, \
						char *found, t_arg_parse_error *on_error);

/* cmd_echo.c */
int						cmd_echo(char *const *args, t_state *state);

/* cmd_cd.c */
int						cmd_cd(char *const *args, t_state *state);

/* get_cd_target.c */
char					*get_cd_target(char *const *args, t_state *state, \
							bool *p_flag);

/* cmd_export.c */
int						cmd_export(char *const *args, t_state *state);

/* export_set.c */
int						export_set(const char *name, const char *value, \
						char *const **env);

/* cmd_hash.c */
int						cmd_hash(char *const *args, t_state *state);

/* cmd_jobs.c */
int						cmd_jobs(char *const *args, t_state *state);

/* cmd_fg.c */
int						cmd_fg(char *const *args, t_state *state);

/* cmd_bg.c */
int						cmd_bg(char *const *args, t_state *state);

/* fg_bg_utils.c */
t_job					*get_job(char *const *args, t_state *state);

/* cmd_fc.c */
int						cmd_fc(char *const *args, t_state *state);

/* cmd_fc_flags.c */
int						cmd_fc_parse_flags(char *const *args, char *valid,
							char *found, t_arg_parse_error *on_error);

/* cmd_fc_editor.c */
bool					cmd_fc_history_edit(char *editor, t_fc_range *range,
							t_state *state);

/* cmd_fc_editor_write.c */
bool					cmd_fc_write_commands_to_file(t_fc_range *range,
							t_state *state);

/* cmd_fc_editor_read.c */
int						cmd_fc_read_and_execute_file(t_state *state);

/* cmd_fc_range.c */
bool					cmd_fc_parse_range(char *const *args, char *flags,
							t_fc_range *range, t_state *state);

/* cmd_fc_range_utils.c */
void					cmd_fc_reverse_range(t_fc_range *range);

/* cmd_fc_replace.c */
void					cmd_fc_parse_replacements(char *const *args,
							char *result[FC_MAX_REPLACE]);
char					*cmd_fc_apply_replacements(char *src,
							char *spec[FC_MAX_REPLACE]);

/* cmd_fc_utils.c */
bool					cmd_fc_check_empty_history_errors(t_state *state,
							char *flags);

/* cmd_exit.c */
int						cmd_exit(char *const *args, t_state *state);

/* cmd_execute_script.c */
int						cmd_execute_script(char *const *args, t_state *state);

/* cmd_set.c */
int						cmd_set(char *const *args, t_state *state);

/* cmd_test.c */
int						cmd_test(char *const *args, t_state *state);

/* cmd_test_files.c */
int						cmd_test_does_file_type_match(char *path, char type);
int						cmd_test_does_file_have_permission(char *path,
							char permission);
int						cmd_test_file_has_data(char *path);

/* cmd_test_numbers.c */
int						cmd_test_numbers(char *op, char *arg_1, char *arg_2);

/* cmd_true_false.c */
int						cmd_true(char *const *args, t_state *state);
int						cmd_false(char *const *args, t_state *state);

/* cmd_type.c */
int						cmd_type(char *const *args, t_state *state);

/* cmd_unset.c */
int						cmd_unset(char *const *args, t_state *state);

/* check_path_change.c */
int						check_path_change(char *const *args, t_state *state, \
						int ret, bool unset);

/* delete_var.c */
void					delete_var(char *name, char *const **arr);
bool					exported_no_equals(char *name, t_state *state);

/* print_exported.c */
bool					print_exported(char *const *args, t_state *state);
#endif
