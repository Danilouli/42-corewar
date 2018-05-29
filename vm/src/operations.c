/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:26:39 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/29 18:43:11 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		bidir_memcpy(void *dst, void *src, int n, short where)
{
	unsigned char	*s;
	unsigned char	*d;
	unsigned int	len;

	s = src;
	d = dst;
	len = (n < 0) ? -n : n;
	len++;
	while (--len)
		(n < 0) ? (*(d++) = s[where++ % MEM_SIZE])
		: (d[where++ % MEM_SIZE] = *(s++));
}

void		bidir_memset(void *dst, char champ_num, int n, short where)
{
	unsigned char	c;
	unsigned char	*d;

	c = (unsigned char)champ_num;
	d = dst;
	while (n)
	{
		d[where++ % MEM_SIZE] = c;
		n--;
	}
}

static void	init_render(t_render *r, t_map *map, t_champ *champs, t_list **ap)
{
	if (r->win)
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glfwSetWindowUserPointer(r->win, r);
	}
	if (r->ncurses)
	{
		r->npause = 1;
		nodelay(initscr(), 1);
		noecho();
		curs_set(0);
		start_color();
		print_nmap(ap, map, r, champs);
	}
}

void		mainloop(t_render *r, t_map *map, t_champ *champs, t_list **ap)
{
	t_list *tmp;

	while (r->pause)
		render(r, map);
	while (r->npause)
		controls_ncurses(r, ap, map, champs);
	tmp = *ap;
	while ((tmp && (int)(CTD - (int)(CYCLE_DELTA * map->round)) > 0)
	&& processit(map, ap, champs, (t_process *)tmp->content))
		tmp = tmp->next;
	if (map->cycles >= map->cycle_todie)
	{
		*ap = proc_filter(*ap, map->p_map);
		if ((++map->checks >= MAX_CHECKS || map->lives >= NBR_LIVE)
		&& !(map->checks = 0))
			map->round++;
		map->cycle_todie = (int)CTD - (int)(CYCLE_DELTA * map->round);
		map->cycles = 0;
		map->lives = 0;
	}
	if (r->win && !(map->t_cycles % r->skip))
		render(r, map);
	else if (r->ncurses && print_nmap(ap, map, r, champs))
		controls_ncurses(r, ap, map, champs);
}

void		process_operations(t_render *r, t_map *map, t_champ *champs,
			t_list **allprocess)
{
	map->cycles = 0;
	map->t_cycles = 0;
	map->round = 0;
	map->checks = 0;
	map->cycle_todie = CTD;
	init_render(r, map, champs, allprocess);
	while (champ_isalive(map, *allprocess, champs) && --map->dump)
		mainloop(r, map, champs, allprocess);
	ft_lstdel(allprocess, &delprocess);
}
