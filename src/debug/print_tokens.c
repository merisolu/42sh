/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:35:59 by amann             #+#    #+#             */
/*   Updated: 2022/10/27 11:59:28 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_tokens(t_token *result)
{
	t_token	*temp;

	temp = result;
	ft_putendl("########## TOKENS ##########");
	while (temp)
	{
		ft_printf("type = %d || value = %s\n", temp->type, temp->value);
		temp = temp->next;
	}
}
