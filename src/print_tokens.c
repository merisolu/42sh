/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:35:59 by amann             #+#    #+#             */
/*   Updated: 2022/10/23 17:36:27 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_tokens(t_token *result)
{
	t_token *temp = result;
	ft_putendl("########## TOKENS ##########");
	while (temp)
	{
		ft_printf("type = %d || value = %s\n", temp->type, temp->value);
		temp = temp->next;
	}
}
