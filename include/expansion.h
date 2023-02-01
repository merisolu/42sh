/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:12 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/01 15:49:13 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

/* Includes */

# include <pwd.h>

# include "libft.h"
# include "general.h"
# include "environment.h"

/* Files */

/* expand_tilde.c */
int		expand_tilde(t_token **cursor, t_state *state, char **result);

/* expand_name.c */
int	expand_name(char *value, t_state *state, char **res);

/* expand_variables.c */
int		expand_variable(t_token **cursor, t_state *state, char **result);

/* expand_hash_percent.c */
int	expand_hash_percent(t_token **cursor, t_state *state, char **res, t_token *param);

/* expand_plus_minus.c */
int	expand_plus_minus(t_token **cursor, t_state *state, char **res, t_token *param);

/* expand_to_value_len.c */
int	expand_to_value_len(char *name, t_state *state, char **res);

/* expand_node.c */
void	expansions_loop(t_token **cursor, t_state *state, char **result, bool recurs);
bool	expand_node(char **word, t_state *state);

/* expansions_retokenize.c */
t_token	*expansions_retokenize(char *line);

/* expansion_utils.c */
bool	var_exists_and_set(char *name, t_state *state);
void	move_cursor_to_end(t_token **cursor, t_state *state);
void	set_braces_state(t_state *state);

/* parse_expansions.c */
bool	parse_expansions(t_ast *root, t_state *state);
#endif
