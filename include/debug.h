/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/12/20 15:35:40 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/* Includes */

# include <fcntl.h>

# include "libft.h"
# include "general.h"
# include "environment.h"

/* Macros */
# define TMP_FILE_PATH "/tmp/.tmp_print_file"

/* Files */

/* ast_print_debug.c */
void	print_ast(t_ast **ast, int fd);

/* check_print_ast.c */
void	check_print_ast(t_ast **ast_list, t_state *state, bool exp);

#endif
