/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_jmp_live.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:56:03 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/28 14:56:04 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	zjmp(t_map *map, t_champ *champ, t_process *p, t_list **allp)
{
	short	param;

	(void)champ;
	(void)allp;
	bidir_memcpy(&param, map->map, -2, p->ptr + 1);
	ft_short_endian_swap((unsigned short*)&param);
	param %= IDX_MOD;
	if (p->carry)
		return ((short)param - 1);
	return (2);
}

int	aff(t_map *map, t_champ *champ, t_process *p, t_list **allp)
{
	t_arg				*arg;
	int					*param;
	int					inc;

	(void)champ;
	(void)allp;
	arg = get_arg(map, p, g_vm[p->op - 1].nb_p, &inc);
	if (!(param = (int*)tabarg(arg, map, p)))
		return (inc - 1);
	ft_printf("%c\n", (char)(param[0] % 256));
	return (2);
}

int	live(t_map *map, t_champ *champ, t_process *p, t_list **allp)
{
	unsigned char	tmp[4];
	unsigned		*cast;

	(void)allp;
	bidir_memcpy(&tmp, map->map, -RS, p->ptr + 1);
	cast = (unsigned *)tmp;
	ft_endian_swap(cast);
	p->life = map->cycle_todie;
	map->lives++;
	if (LIFECODE - *cast >= champslen(champ))
		return (4);
	champ[LIFECODE - *cast].lastlife = map->t_cycles;
	return (4);
}
