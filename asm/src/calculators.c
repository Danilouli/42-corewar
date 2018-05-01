/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <acouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:53:02 by dsaadia           #+#    #+#             */
/*   Updated: 2018/05/01 17:59:14 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

static void helper_len(t_line *line, int *len_tot)
{
	int i;

	i = -1;
	line->len = 1;
	if (OPL(line).mod_c)
		(line->len)++;
	while (++i < line->nb_params)
	{
		if (is_direct(line->param[i]))
			line->len += (OPL(line).need_c) ? 2 : 4;
		else if (is_indirect(line->param[i]))
			line->len += 2;
		else if (is_reg(line->param[i]))
			line->len += 1;
	}
	*len_tot += line->len;
	line->len_tot = *len_tot;
	line->addr = line->len_tot - line->len;
}

void	calc_len(t_line *line)
{
	static int len_tot = 0;

	if (!(line->opcode))
	{
		LAST_LABEL = line->label;
		ft_printf("lastlab %s\n", LAST_LABEL);
		return ;
	}
	if (LAST_LABEL)
	{
		line->label = LAST_LABEL;
		LAST_LABEL = 0;
	}
	helper_len(line, &len_tot);
}

void endian_swap(unsigned int *ptr)
{
	unsigned int 		tmp;

	tmp = *ptr;
	*ptr = ((tmp>>24) & 0xff) | ((tmp<<8) & 0xff0000) | ((tmp>>8) & 0xff00)
	| ((tmp<<24) & 0xff000000);
}

void short_endian_swap(unsigned short *ptr)
{
	unsigned short		tmp;

	tmp = *ptr;
	*ptr = (tmp>>8) | (tmp<<8);
}

int create_ocp(t_line *line)
{
	int i;
	static int	regcode = REG_CODE;
	static int	dircode = DIR_CODE;
	static int	indcode = IND_CODE;
	int	ret;

	i = 0;
	ret = 0;
	while (i < line->nb_params)
	{
		if (is_reg((line->param)[i]))
			ret = ret | (regcode << (6 - 2 * i));
		else if (is_direct((line->param)[i]))
			ret = ret | (dircode << (6 - 2 * i));
		else if (is_indirect((line->param)[i]))
			ret = ret | (indcode << (6 - 2 * i));
		i++;
	}
	return (ret);
}
