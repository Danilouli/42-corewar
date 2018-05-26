#include "corewar.h"

void	bidir_memcpy(void *dst, void *src, int n, short where)
{
	unsigned char	*s;
	unsigned char	*d;
	unsigned int	len;

	s = src;
	d = dst;
	len = (n < 0) ? -n : n;
	while (len)
	{
		// printf("Where = %hi\n", where);
		if (n < 0)
			*(d++) = s[where++ % MEM_SIZE];
		else
			d[where++ % MEM_SIZE] = *(s++);
		len--;
	}
}

void	bidir_memset(void *dst, char champ_num, int n, short where)
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

void	process_operations(t_render *r, t_map *map, t_champ *champs,
		t_list **allprocess)
{
	t_list			*tmp;

	map->cycles = 0;
	map->t_cycles = 0;
	map->round = 0;
	map->checks = 0;
	map->cycle_todie = CYCLE_TO_DIE;
	if (r->win) {
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
		print_nmap(allprocess, map, r, champs);
	}
	while (champ_isalive(map, *allprocess, champs))
/*|| (r->win && !glfwWindowShouldClose(r->win))*/ // // Doit rester dans cet ordre
	{
		while (r->pause)
			render(r, map);
		while (r->npause)
			controls_ncurses(r, allprocess, map, champs);
		tmp = *allprocess;
		while (tmp && (int)(CYCLE_TO_DIE - (int)(CYCLE_DELTA * map->round)) > 0)
		{
			processit(map, allprocess, champs, (t_process *)tmp->content);
			tmp = tmp->next;
		}
		// printf("cycle: %i | toie: %ji\n", map->cycles, map->cycle_todie);
		if (map->cycles >= map->cycle_todie)
		{
			*allprocess = proc_filter(*allprocess, map->p_map);
			// printf("len: %zu\n", ft_lstlen(*allprocess));
			if (++map->checks >= MAX_CHECKS || map->lives >= NBR_LIVE)
			{
				map->checks = 0;
				map->round++;
			}
			map->cycle_todie = (int)CYCLE_TO_DIE - (int)(CYCLE_DELTA * map->round);
			map->cycles = 0;
			map->lives = 0;
		}
		if (r->win && !(map->t_cycles % r->skip))
			render(r, map);
		else if (r->ncurses)
		{
			print_nmap(allprocess, map, r, champs);
			controls_ncurses(r, allprocess, map, champs);
		}
	}
	ft_lstdel(allprocess, &delprocess);
}
