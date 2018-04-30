/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verificators4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:11:11 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/30 20:20:54 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int is_real_code_helper(t_list *s)
{
	int i;
	char *label;
	char *pstr;
	int addr;

	i = -1;
	while (++i < LINECONT(s)->nb_params)
	{
		pstr = LINECONT(s)->param[i];
		if (is_direct(pstr) && (label = is_label_dir(pstr)))
		{
			if ((addr = is_real_label(label)) == -1)
				return (0);
			ft_memdel((void**)&LINECONT(s)->param[i]);
			LINECONT(s)->param[i] = reinit_direct(&pstr, addr, LINECONT(s)->addr);
		}
		else if (is_indirect(pstr) && (label = is_label_ind(pstr)))
		{
			if ((addr = is_real_label(label)) == -1)
				return (0);
			LINECONT(s)->param[i] = reinit_indirect(&pstr, addr, LINECONT(s)->addr);
		}
	}
	return (1);
}

int	is_real_code(void)
{
	t_list	*surf;

	surf = g_lines;
	while (surf)
	{
		if (surf->content_size == 2)
		{
			if (!is_real_code_helper(surf))
				return (0);
		}
		surf = surf->next;
	}
	return (1);
}

int is_relabel(char *str)
{
	t_list *surf;

	surf = g_labels;
	if (!is_label(str))
		return (0);
	while (surf)
	{
		if (ft_strnequ(LABCONT(surf)->value, str, ft_strlen(str) - 1))
			return (1);
		surf = surf->next;
	}
	return (0);
}
