/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verificators3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 19:56:36 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/31 16:31:46 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int		what_is(char *str)
{
	if (is_reg(str))
		return (1);
	if (is_direct(str))
		return (2);
	if (is_indirect(str))
		return (4);
	return (0);
}

char	*is_label_dir(char *dir)
{
	if (dir[1] != LABEL_CHAR)
		return (0);
	return (dir + 2);
}

char	*is_label_ind(char *ind)
{
	if (ind[0] != LABEL_CHAR)
		return (0);
	return (ind + 1);
}

int		is_real_label(char *str)
{
	t_list	*surf;
	int		isend;
	char	*final_label;

	isend = 0;
	surf = g_lines;
	final_label = fetch_final_label(str, &isend);
	if (!final_label && isend)
		return (-2);
	else if (!final_label && !isend)
		return (-1);
	while (surf)
	{
		if (surf->content_size == 2)
		{
			if (LINECONT(surf)->label &&
				ft_strequ(LINECONT(surf)->label, final_label))
				return (LINECONT(surf)->addr);
		}
		surf = surf->next;
	}
	return (-1);
}
