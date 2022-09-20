/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_conv_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:37:03 by amann             #+#    #+#             */
/*   Updated: 2022/03/10 16:47:32 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_conv_type_helper(char c, t_conv *conv)
{
	if (c == 'b')
		conv->b = TRUE;
	else if (c == 'n')
		conv->n = TRUE;
	else if (c == 'f')
		conv->f = TRUE;
	else if (c == '%')
		conv->percent = TRUE;
	else if (c == 'c')
		conv->c = TRUE;
	else if (c == 's')
		conv->s = TRUE;
	else if (c == 'p')
		conv->p = TRUE;
}

static int	check_numeric(char c)
{
	if (c == 'd' || c == 'i' || c == 'o')
		return (TRUE);
	if (c == 'u' || c == 'x' || c == 'X')
		return (TRUE);
	if (c == 'p' || c == 'b')
		return (TRUE);
	return (FALSE);
}

void	set_conv_type(char c, t_conv *conv)
{
	if (check_numeric(c))
		conv->numeric = TRUE;
	if (c == 'd' || c == 'i')
		conv->d = TRUE;
	else if (c == 'o')
		conv->o = TRUE;
	else if (c == 'u')
		conv->u = TRUE;
	else if (c == 'x')
		conv->x = TRUE;
	else if (c == 'X')
		conv->big_x = TRUE;
	set_conv_type_helper(c, conv);
}
