/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetchers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:29:09 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/07 18:32:37 by dsaadia          ###   ########.fr       */
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
