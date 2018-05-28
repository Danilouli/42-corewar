/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_i.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:47:06 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/28 15:47:07 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ld(t_map *map, t_champ *champ, t_process *p, t_list **allp)
{
	t_arg				*arg;
	int					inc;
	int					*param;

	(void)champ;
	(void)allp;
	arg = get_arg(map, p, op_tab[p->op - 1].nb_p, &inc);
	if (!(param = (int*)tabarg(arg, map, p)))
		return (inc);
	if (p->op < 13 && arg[0].type == DC)
		ft_endian_swap((unsigned *)&param[0]);
	ft_memcpy(&p->reg[RS * param[1]], &param[0], RS);
	p->carry = param[0] ? 0 : 1;
	return (inc);
}

int			ldi(t_map *map, t_champ *champ, t_process *p, t_list **allp)
{
	t_arg				*arg;
	int					inc;
	int					*param;
	int					tmp;

	(void)champ;
	(void)allp;
	arg = get_arg(map, p, op_tab[p->op - 1].nb_p, &inc);
	if (!(param = (int*)tabarg(arg, map, p)))
		return (inc);
	assign_param(param, arg, p);
	tmp = p->ptr + (param[0] + param[1]) % ((p->op < 13) ? IDX_MOD : MEM_SIZE);
	tmp = tmp < 0 ? MEM_SIZE + tmp : tmp;
	tmp = tmp >= MEM_SIZE ? tmp - MEM_SIZE : tmp;
	bidir_memcpy(&p->reg[RS * param[2]], map->map, -RS, tmp);
	if (p->op > 12)
	{
		param = (int *)&p->reg[RS * param[2]];
		p->carry = *param ? 0 : 1;
	}
	return (inc);
}
