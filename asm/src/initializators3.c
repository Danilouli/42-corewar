/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializators3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 12:18:21 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/01 19:51:19 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

void redefine_labels(char *final_label)
{
	t_list *surf;

	surf = g_labels;
	while (surf)
	{
		if (ft_strequ(LABCONT(surf)->value, final_label))
		{
			LABCONT(surf)->real_label = final_label;
			return ;
		}
		if (!(LABCONT(surf)->real_label))
			LABCONT(surf)->real_label = final_label;
		surf = surf->next;
	}
}
