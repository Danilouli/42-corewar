/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:58:06 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/28 14:58:07 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_arg			*get_arg(t_map *map, t_process *p, int nbarg, int *in)
{
	size_t			a;
	unsigned char	ocp;
	unsigned char	*translation;
	static t_arg	arg[4];
	int				inc;

	*in = 1;
	(void)nbarg;
	ft_bzero(arg, sizeof(t_arg) * 4);
	ocp = map->map[(*in + p->ptr) % MEM_SIZE];
	translation = translate_ocp(ocp);
	*in += (op_tab[p->op - 1].mod_c) ? 1 : 0;
	a = 0;
	while (a < (size_t)op_tab[p->op - 1].nb_p)
	{
		ft_bzero(arg[a].arg, 4);
		inc = 0;
		if (!(arg[a].type = *translation))
			return (retin(in));
		if (arg[a].type == RC)
			bidir_memcpy(arg[a].arg, map->map, inc = -T_REG, *in + p->ptr);
		else if (arg[a].type == DC || (p->op == 3 && arg[a].type == IC))
			bidir_memcpy(arg[a].arg, map->map, inc = -((op_tab[p->op - 1].need_c
			|| (p->op == 3 && arg[a].type == IC)) ? 2 : 4), *in + p->ptr);
		else if (arg[a].type == IC)
			bidir_memcpy(arg[a].arg, map->map, inc = -T_DIR, *in + p->ptr);
		else
			return (retin(in));
		arg[a++].len = (size_t)-inc;
		*in -= (int)inc;
		translation++;
	}
	arg[a].type = 0;
	*in = *in - 1;
	return (arg);
}

unsigned		*tabarg(t_arg *arg, t_map *map, t_process *process)
{
	static unsigned	param[3];
	short			cast;
	size_t			a;
	size_t			i;

	a = 0;
	i = 1;
	ft_bzero(param, sizeof(unsigned) * 3);
	if (!arg || !ocpcheck(map, process))
		return (0);
	while (a < (size_t)op_tab[process->op - 1].nb_p)
	{
		if (arg[a].type == RC && *arg[a].arg > 0 && *arg[a].arg <= REG_NUMBER)
			param[a] = (*arg[a].arg) - 1;
		else if (arg[a].type == DC || (process->op == 3 && arg[a].type == IC))
		{
			param[a] = (op_tab[process->op - 1].need_c
			|| (process->op == 3 && arg[a].type == IC))
			? (short)ft_short_endian_swap((unsigned short*)arg[a].arg)
			: (int)ft_endian_swap((unsigned *)arg[a].arg);
		}
		else if (arg[a].type == IC)
		{
			cast = (short)ft_short_endian_swap((unsigned short *)arg[a].arg);
			if (process->op < 13)
				cast %= IDX_MOD;
			cast = cast < 0 ? MEM_SIZE + cast : cast;
			cast = cast >= MEM_SIZE ? cast - MEM_SIZE : cast;
			bidir_memcpy(&param[a], map->map, -RS, process->ptr + cast);
		}
		else
			return (NULL);
		a++;
	}
	return (param);
}
