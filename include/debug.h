/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:32:07 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 14:01:14 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/* Includes */

# include "libft.h"
# include "general.h"

/* Files */

/* ast_print_debug.c */
void	print_ast(t_ast **tree);

/* print_tokens.c */
void	print_tokens(t_token *result);

#endif
