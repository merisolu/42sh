/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/11/16 17:07:52 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/* Includes */

# include "libft.h"
# include "general.h"
# include "environment.h"
# include "execution.h"

/* needed to delete temp files with remove() */
# include <stdio.h>

/* Macros */
# define TMP_FILE_PATH "/tmp/.tmp_print_file"

/* Files */

/* ast_print_debug.c */
void	print_ast(t_ast **ast, int fd);

/* check_print_ast.c */
void	check_print_ast(t_ast **ast_list, t_state *state, bool exp);

/* print_tokens.c */
void	print_tokens(t_token *result);

#endif
