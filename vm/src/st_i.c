/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_i.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:00:00 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/29 15:00:02 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		st(t_map *map, t_champ *champ, t_process *p, t_list **allp)
{
	t_arg	*arg;
	int		inc;
	int		*param;
	short	cast;

	(void)champ;
	(void)allp;
	arg = get_arg(map, p, g_vm[p->op - 1].nb_p, &inc);
	if (!(param = (int*)tabarg(arg, map, p)))
		return (inc - 1);
	if (arg[1].type == T_REG)
		ft_memcpy(&p->reg[param[1] * RS], &p->reg[param[0] * RS], RS);
	else
	{
		cast = (short)param[1] % (short)IDX_MOD + p->ptr;
		cast = cast < 0 ? MEM_SIZE + cast : cast;
		cast = cast >= MEM_SIZE ? cast - MEM_SIZE : cast;
		bidir_memcpy(map->map, &p->reg[param[0] * RS], RS, cast);
		bidir_memset(map->c_map, p->champ->num + 1, RS, cast);
	}
	return (inc);
}

void	assign_stiparam(int *param, t_arg *arg, t_process *p)
{
	int tmp;

	if (arg[1].type == RC)
	{
		tmp = (int)*(int *)&p->reg[RS * param[1]];
		param[1] = (int)(ft_endian_swap((unsigned *)&tmp));
	}
	if (arg[2].type == RC)
	{
		tmp = (int)*(int *)&p->reg[RS * param[2]];
		param[2] = (int)(ft_endian_swap((unsigned *)&tmp));
	}
	if (arg[1].type == IC)
		param[1] = (int)(ft_endian_swap((unsigned *)&param[1]));
	if (arg[2].type == IC)
		param[2] = (int)(ft_endian_swap((unsigned *)&param[2]));
}

int		sti(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg	*arg;
	int		inc;
	int		*param;
	int		tmp;

	(void)champ;
	(void)allprocess;
	arg = get_arg(map, process, g_vm[process->op - 1].nb_p, &inc);
	if (!(param = (int*)tabarg(arg, map, process)))
		return (inc);
	assign_stiparam(param, arg, process);
	tmp = (param[1] + param[2]) % IDX_MOD + process->ptr;
	tmp = tmp < 0 ? MEM_SIZE + tmp : tmp;
	tmp = tmp >= MEM_SIZE ? tmp - MEM_SIZE : tmp;
	bidir_memcpy(map->map, &process->reg[param[0] * RS], RS, tmp);
	bidir_memset(map->c_map, process->champ->num + 1, RS, tmp);
	return (inc);
}
