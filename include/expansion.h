/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:12 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/20 15:28:16 by jumanner         ###   ########.fr       */
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

/* expand_variables.c */
int		expand_variable(t_token **cursor, t_state *state, char **result);

/* expand_node.c */
bool	expand_node(char **word, t_state *state);

/* parse_expansions.c */
bool	parse_expansions(t_ast *root, t_state *state);
#endif
