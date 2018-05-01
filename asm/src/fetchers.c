/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetchers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:29:09 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/01 22:53:49 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		fetch_opcode(char *op_name)
{
	int i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strequ(op_name, g_op_tab[i].name))
		{
			ft_strdel(&op_name);
			return (g_op_tab[i].code);
		}
		i++;
	}
	ft_strdel(&op_name);
	return (0);
}

char	*fetch_final_label(char *label)
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
