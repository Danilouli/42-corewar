/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:58:06 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/29 16:34:53 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <limits.h>

int				argue(t_arg *arg, t_map *map, t_process *p, int *in)
{
	int		inc;

	ft_bzero(arg->arg, 4);
	if (arg->type == RC)
		bidir_memcpy(arg->arg, map->map, inc = -T_REG, *in + p->ptr);
	else if (arg->type == DC || (p->op == 3 && arg->type == IC))
		bidir_memcpy(arg->arg, map->map, inc = -((op_tab[p->op - 1].need_c
		|| (p->op == 3 && arg->type == IC)) ? 2 : 4), *in + p->ptr);
	else if (arg->type == IC)
		bidir_memcpy(arg->arg, map->map, inc = -T_DIR, *in + p->ptr);
	else
		return (-1);
	arg->len = (size_t)-inc;
	*in -= (int)inc;
	return (1);
}

t_arg			*get_arg(t_map *map, t_process *p, int nbarg, int *in)
{
	size_t			a;
	unsigned char	*translation;
	static t_arg	arg[4];

	*in = 1;
	(void)nbarg;
	ft_bzero(arg, sizeof(t_arg) * 4);
	translation = translate_ocp(map->map[(*in + p->ptr) % MEM_SIZE]);
	*in += (op_tab[p->op - 1].mod_c) ? 1 : 0;
	a = 0;
	while (a < (size_t)op_tab[p->op - 1].nb_p)
	{
		if (!(arg[a].type = *translation++))
			return (retin(in));
		if ((argue(&arg[a++], map, p, in)) == -1)
			return (retin(in));
	}
	arg[a].type = 0;
	*in = *in - 1;
	return (arg);
}

int				ton_bar(t_arg *arg, unsigned *param, t_map *map, t_process *p)
{
	short			cast;

	if (arg->type == RC && *arg->arg > 0 && *arg->arg <= REG_NUMBER)
		(*param) = (*arg->arg) - 1;
	else if (arg->type == DC || (p->op == 3 && arg->type == IC))
		(*param) = (op_tab[p->op - 1].need_c
		|| (p->op == 3 && arg->type == IC))
		? (short)ft_short_endian_swap((unsigned short*)arg->arg)
		: (int)ft_endian_swap((unsigned *)arg->arg);
	else if (arg->type == IC)
	{
		cast = (short)ft_short_endian_swap((unsigned short *)arg->arg);
		if (p->op < 13)
			cast %= IDX_MOD;
		cast = cast < 0 ? MEM_SIZE + cast : cast;
		cast = cast >= MEM_SIZE ? cast - MEM_SIZE : cast;
		bidir_memcpy(&param[0], map->map, -RS, p->ptr + cast);
	}
	else
		return (-1);
	return (1);
}

unsigned		*tabarg(t_arg *arg, t_map *map, t_process *process)
{
	static unsigned	param[3];
	size_t			a;

	a = 0;
	ft_bzero(param, sizeof(unsigned) * 3);
	if (!arg || !ocpcheck(map, process))
		return (0);
	while (a < (size_t)op_tab[process->op - 1].nb_p)
	{
		if ((ton_bar(&arg[a], &param[a], map, process)) == -1)
			return (NULL);
		a++;
	}
	return (param);
}
