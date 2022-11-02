/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:06 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/02 12:02:23 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

/* Includes */

# include "libft.h"
# include "general.h"
# include "execution.h"
# include "utils.h"
# include "environment.h"

/* Types */

typedef int	t_cmd(char *const *args, t_state *state);

typedef struct s_cmd_dispatch
{
	const char	*name;
	t_cmd		*run;
}	t_cmd_dispatch;

typedef struct s_cmd_env
{
	int		exclusive;
	char	**args;
	char	**env;
}	t_cmd_env;

/* Files */

/* built_ins.c */
t_cmd	*built_in_get(const char *name);
char	*built_in_search(const char *partial_name);
pid_t	built_in_run(t_cmd cmd, char *const *args, t_state *state, \
		t_ast_execution *ast);

/* cmd_echo.c */
int		cmd_echo(char *const *args, t_state *state);

/* cmd_cd.c */
int		cmd_cd(char *const *args, t_state *state);

/* cmd_env.c */
int		cmd_env(char *const *args, t_state *state);

/* cmd_setenv.c */
int		cmd_setenv(char *const *args, t_state *state);

/* cmd_unsetenv.c */
int		cmd_unsetenv(char *const *args, t_state *state);

/* cmd_exit.c */
int		cmd_exit(char *const *args, t_state *state);

#endif
