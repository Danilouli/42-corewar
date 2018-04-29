/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetchers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:29:09 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/29 13:13:28 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int	fetch_opcode(char *op_name)
{
	int i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strequ(op_name, g_op_tab[i].name))
			return (g_op_tab[i].code);
		i++;
	}
	return (0);
}

char *fetch_final_label(char *label)
{
	t_list *surf;

	surf = g_labels;
	while (surf)
	{
		if (ft_strequ(label, LABCONT(surf)->value))
			return (LABCONT(surf)->real_label);
		surf = surf->next;
	}
	return (NULL);
}
