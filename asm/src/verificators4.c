/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verificators4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:11:11 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/01 22:35:08 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static int	dir_case(char *lab, int i, char *pstr, t_list *s)
{
	int		addr;

	if (!lab[0])
		return ((int)super_herror("Label vide", 0));
	if ((addr = is_real_label(lab)) == -1)
		return (0);
	ft_memdel((void**)&LINECONT(s)->param[i]);
	LINECONT(s)->param[i] = reinit_direct(&pstr, addr, LINECONT(s)->addr);
	return (1);
}

static int	ind_case(char *lab, int i, char *pstr, t_list *s)
{
	int		addr;

	if (!lab[0])
		return ((int)super_herror("Label vide", 0));
	if ((addr = is_real_label(lab)) == -1)
		return (0);
	ft_memdel((void**)&LINECONT(s)->param[i]);
	LINECONT(s)->param[i] = reinit_indirect(&pstr, addr, LINECONT(s)->addr);
	return (1);
}

static int	is_real_code_helper(t_list *s)
{
	int		i;
	char	*lab;
	char	*pstr;

	i = -1;
	while (++i < LINECONT(s)->nb_params)
	{
		pstr = LINECONT(s)->param[i];
		if (is_direct(pstr) && (lab = is_label_dir(pstr)))
		{
			if (!dir_case(lab, i, pstr, s))
				return (0);
		}
		else if (is_indirect(pstr) && (lab = is_label_ind(pstr)))
			if (!ind_case(lab, i, pstr, s))
				return (0);
	}
	return (1);
}

int			is_real_code(void)
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

int			is_relabel(char *str)
{
	t_list	*surf;

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
