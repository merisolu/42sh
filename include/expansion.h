/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:12 by jumanner          #+#    #+#             */
/*   Updated: 2023/02/17 13:18:27 by jumanner         ###   ########.fr       */
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

/* expand_hash.c */
void	handle_hash_expansion(t_state *state, char *temp_res, char *temp_exp);

/* expand_name.c */
int		expand_name(char *value, t_state *state, char **res);

/* expand_node.c */
void	expansions_loop(t_token **cursor, t_state *state, char **result, \
		bool recurs);
bool	expand_node(char **word, t_state *state, bool autocomp);

/* expand_percent.c */
void	handle_percent(t_state *state, char *temp_res, char *temp_exp);

/* expand_plus_minus.c */
int		expand_plus_minus(t_token **cursor, t_state *state, char **res, \
		t_token *param);

/* expand_tilde.c */
int		expand_tilde(t_token **cursor, t_state *state, char **result);

/* expand_to_value_len.c */
int		expand_to_value_len(t_token **cursor, t_state *state, char **res);

/* expand_variables.c */
int		expand_variable(t_token **cursor, t_state *state, char **result);

/* expansions_retokenize.c */
t_token	*expansions_retokenize(char *line);

/* expansion_utils.c */
bool	var_exists_and_set(char *name, t_state *state);
void	move_cursor_to_end(t_token **cursor, t_state *state);
void	set_braces_state(t_state *state);

/* parse_expansions.c */
bool	parse_expansions(t_ast *root, t_state *state);

/* pattern_matching_control.c */
int		pattern_matching_control(t_token **cursor, t_state *state, char **res, \
		t_token *param);

/* tilde_param_exp.c */
bool	check_param_exp(t_state *s, t_token *fb);
bool	check_recursive(t_token **csr, t_state *s, t_token *fb, \
		t_token_type token_type);

/* tilde_if_checks.c */
bool	basic_exp(t_token **csr, t_token *fb, t_state *s, t_token_type scn);
bool	minus_exp(t_token **csr, t_token *fb, t_state *s, t_token_type scn);
bool	plus_exp(t_token **csr, t_token *fb, t_state *s, t_token_type scn);
#endif
