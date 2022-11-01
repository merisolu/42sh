/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:08:42 by jumanner          #+#    #+#             */
/*   Updated: 2022/10/27 15:11:18 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

/* Includes */

# include <dirent.h>

# include "libft.h"
# include "general.h"
# include "built_ins.h"

/* Files */

/* autocomplete.c */
int	autocomplete(t_state *state);

#endif
