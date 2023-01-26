/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:16 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/26 13:31:24 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* Includes */

# include "ast.h"

/* Files */

/* check_quotes.c */
void			check_quotes(char c, t_tokenizer *tokenizer);

/* eat_read_token.c */
bool			eat_token(\
	t_token **cursor, t_token_type type, t_token *on_fail);
bool			read_token(\
	t_token **cursor, t_token_type type, t_token *on_fail);

/* get_token_type.c */
t_token_type	get_token_type(char value, bool in_quotes, bool in_braces, \
bool backslash_inhibited);

/* lexer.c */
t_token			*tokenize(char *input, t_tokenizer *tokenizer);

/* literals.c */
int				check_literals(\
	t_token **cursor, t_state *state, char **result);

/* add_to_result.c */
int				add_to_result(char **result, char *value, t_state *state);

/* token.c */
t_token			*token_add(t_token **list, t_token_type type, char *value);
void			token_free(t_token **token);

/* token_list.c */
void			token_list_free(t_token **list);

#endif
