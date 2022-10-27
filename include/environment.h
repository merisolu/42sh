/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:09 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 14:01:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

/* Includes */

# include "libft.h"
# include "general.h"
# include "util.h"

/* Files */

/* environment.c */
int		env_set(const char *name, const char *value, char *const **env);
int		env_unset(const char *name, char *const **env);
void	env_print_all(char *const *env);
size_t	valid_env_name_length(char *name);

/* environment_getters.c */
char	*env_get(const char *name, char *const *env);
char	*env_get_or(char *name, char *on_fail, char *const *env);
char	**env_get_pointer(const char *name, char *const *env);

/* shlvl.c */
int		set_shlvl(char *const **env);

#endif
