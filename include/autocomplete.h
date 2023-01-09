/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:08:42 by jumanner          #+#    #+#             */
/*   Updated: 2023/01/09 15:42:21 by amann            ###   ########.fr       */
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
int	autocomplete(t_state *state, bool tab);

#endif
