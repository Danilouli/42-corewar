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

static inline void 	init_action(t_process *process, t_map *map)
{
	if (!process->active && map->map[process->ptr] > 0 && map->map[process->ptr] < 17)
	{
		process->op = map->map[process->ptr];
		process->cycles = op_tab[map->map[process->ptr] - 1].cycles;
		process->active = 1;
	}
	process->cycles -= (process->active) ? 1 : 0;
}

static inline void 	launch_action(t_process *process, t_map *map, t_champ *champs, \
					t_list **allprocess)
{
	int toadd = 0;
	static	int	(*f[17])(t_map *, t_champ *, t_process *, t_list **allprocess) = {
		&live, &ld, &st, &add, &sub, &and, &or, &xor, &zjmp, &ldi, &sti, &cfork,
		&ld, &ldi, &lcfork, &aff, NULL
	};

	if (map->map[process->ptr] > 0 && map->map[process->ptr] < 17 && process->active
	&& !process->cycles && process->op)
	{
		toadd = f[(size_t)process->op - 1](map, champs, process, allprocess);
		// printf("%s| toadd: %i\n", op_tab[process->op - 1].name, toadd);
		process->ptr += toadd;
		process->ptr = (process->ptr < 0) ? MEM_SIZE + process->ptr : process->ptr;
		process->op = 0;
		process->active = 0;
	}
}

void	process_operations(t_render *r, t_map *map, t_champ *champs,
		t_list **allprocess)
{
	t_list			*tmp;
	t_process	*process;
	int			f_ptr;

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
		nodelay(initscr(), 1);
		noecho();
		curs_set(0);
		start_color();
		print_nmap(map);
		refresh();
		r->npause = 1;
	}
	while (champ_isalive(map, *allprocess, champs))
/*|| (r->win && !glfwWindowShouldClose(r->win))*/ // // Doit rester dans cet ordre
	{
		while (r->pause)
			render(r, map);
		while (r->npause)
			controls_ncurses(r);
		tmp = *allprocess;
		while (tmp && (int)(CYCLE_TO_DIE - CYCLE_DELTA * map->round) > 0)
		{
			process = (t_process *)tmp->content;
			f_ptr = process->ptr;
			init_action(process, map);
			launch_action(process, map, champs, allprocess);
			if (!process->active && !process->cycles)
				process->ptr++;
			process->life--;
			process->ptr = process->ptr < 0 ? MEM_SIZE + process->ptr : process->ptr;
			process->ptr = process->ptr >= MEM_SIZE ? process->ptr - MEM_SIZE : process->ptr;
			map->p_map[f_ptr] = 0;
			map->p_map[process->ptr] = 1;
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
			map->cycle_todie = CYCLE_TO_DIE - (CYCLE_DELTA * map->round);
			map->cycles = 0;
			map->lives = 0;
		}
		if (r->win && !(map->t_cycles % r->skip))
			render(r, map);
		else if (r->ncurses)
		{
			print_nmap(map);
			refresh();
			controls_ncurses(r);
		}
	}
}
