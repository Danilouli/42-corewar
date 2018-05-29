/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:54:13 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/29 18:40:32 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_action(t_process *p, t_map *map)
{
	if (!p->active && map->map[p->ptr] > 0 && map->map[p->ptr] < 17)
	{
		p->op = map->map[p->ptr];
		p->cycles = g_vm[map->map[p->ptr] - 1].cycles;
		p->active = 1;
	}
	p->cycles -= (p->active) ? 1 : 0;
}

static void	launch_action(t_process *p, t_map *map, t_champ *champs, \
					t_list **allp)
{
	int			toadd;
	static int	(*f[17])(t_map *, t_champ *, t_process *, t_list **) = {
		&live, &ld, &st, &add, &sub, &and, &or, &xor, &zjmp, &ldi, &sti, &cfork,
		&ld, &ldi, &lcfork, &aff, NULL
	};

	toadd = 0;
	if (p->active && !p->cycles && p->op)
	{
		toadd = f[(size_t)p->op - 1](map, champs, p, allp);
		p->ptr += toadd;
		p->ptr = (p->ptr < 0) ? MEM_SIZE + p->ptr : p->ptr;
		p->op = 0;
		p->active = 0;
	}
}

int			processit(t_map *map, t_list **allp, t_champ *champs, t_process *p)
{
	int			f_ptr;

	f_ptr = p->ptr;
	init_action(p, map);
	launch_action(p, map, champs, allp);
	if (!p->active && !p->cycles)
		p->ptr++;
	p->life--;
	p->ptr = p->ptr < 0 ? MEM_SIZE + p->ptr : p->ptr;
	p->ptr = p->ptr >= MEM_SIZE ? p->ptr - MEM_SIZE : p->ptr;
	map->p_map[f_ptr] ? map->p_map[f_ptr]-- : (void)map->p_map[f_ptr];
	map->p_map[p->ptr]++;
	return (1);
}
