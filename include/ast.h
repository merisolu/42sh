/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:04 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 14:14:49 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/* Includes */

# include "libft.h"
# include "general.h"
# include "utils.h"
# include "parsing.h"
# include "expansion.h"

/* Types */

typedef struct s_token_dispatch
{
	char				symbol;
	t_token_type		token;
}	t_token_dispatch;

typedef int	t_parse_function(t_token **cursor, t_state *state, char **result);

/* Files */

/* ast_add_args.c */
char	**ast_add_args(t_token **cursor);

/* ast_cleanse_args.c */
void	ast_cleanse_ws(t_token **list);

/* ast_free.c */
void	ast_free(t_ast **tree_list);

/* ast_parse_expansions.c */
int		ast_parse_expansions(t_ast *root, t_state *state);

/* ast_pipe_sequence.c */
t_ast	*ast_pipe_sequence(t_token **cursor);

/* ast_redirect_recursion.c */
int		ast_redirect_recursion(t_ast *node, t_token **cursor);

/* ast_retokenize.c */
t_token	*ast_retokenize(char *line);

/* grammar.c */
t_ast	**construct_ast_list(t_token **cursor);

#endif