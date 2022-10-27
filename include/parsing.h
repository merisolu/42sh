/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:16 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 14:15:37 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* Includes */

# include "libft.h"
# include "general.h"
# include "ast.h"

/* Files */

/* eat_read_token.c */
int				eat_token(\
	t_token **cursor, t_token_type type, t_token *on_fail);
int				read_token(\
	t_token **cursor, t_token_type type, t_token *on_fail);

/* get_token_type.c */
t_token_type	get_token_type(char value, int in_quotes);

/* lexer.c */
t_token			*tokenize(char *line);

/* literals.c */
int				check_literals(\
	t_token **cursor, t_state *state, char **result);

/* parser.c */
t_ast			**parse(t_token *list, t_state *state);
int				add_to_result(char **result, char *value, t_state *state);
void			reset_state(t_state *state);

/* token.c */
t_token			*token_add(t_token **list, t_token_type type, char *value);
void			token_free(t_token **token);
int				token_is_word_end(t_token *token);

/* token_list.c */
void			token_list_free(t_token **list);

#endif
