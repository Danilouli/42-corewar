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


unsigned char	*translate_OCP(unsigned char OCP)
{
	int						i;
	unsigned char			mask;
	static unsigned char	res[4];

	i = -1;
	mask = 3;
	ft_bzero(res, 4);
	while (++i < 3)
		res[i] = OCP >> (6 - (i * 2)) & mask;
	return (res);
}

char	OCPCheck(unsigned char OCP, int nbarg)
{
	int						i;
	unsigned char			mask;

	if (nbarg== -1)
		return (1);
	mask = 192;
	i = -1;
	while(++i < nbarg)
		if (!(OCP & (mask >> i * 2)))
			return (0);
	return (!(OCP & (mask >> i * 2)));
}

t_arg	*get_arg(t_map *map, t_process *process, int nbarg)
{
	size_t			a;
	size_t			i;
	unsigned char	OCP;
	unsigned char	*translation;
	static t_arg	arg[4];
	int				inc;

	i = 1;
	(void)nbarg;
	ft_bzero(arg, sizeof(t_arg) * 4);
	OCP = map->map[i + process->ptr < MEM_SIZE ? i + process->ptr : 0];
	if (!OCPCheck(OCP, nbarg))
		return (NULL);
	translation = (op_tab[process->op - 1].mod_c) ? translate_OCP(OCP) : NULL;
	i += (op_tab[process->op - 1].mod_c) ? 1 : 0;
	a = 0;
	while (translation && *translation)
	{
		ft_bzero(arg[a].arg, 4);
		inc = 0;
		arg[a].type = *translation;
		if (arg[a].type == REG_CODE && map->map[i + process->ptr] > 0 && map->map[i + process->ptr] < REG_NUMBER + 1)
		{
			// printf("map->map REG : %i\n", map->map[i + process->ptr]);
			bidir_memcpy(arg[a].arg, map->map, inc = -T_REG, i + process->ptr);
		}
			// ft_memcpy(arg[a].arg, &map->map[i + process->ptr], inc = 1);
		else if (arg[a].type == DIR_CODE || (process->op == 3 && arg[a].type == IND_CODE))
			bidir_memcpy(arg[a].arg, map->map, inc = -((op_tab[process->op - 1].need_c) ? 2 : 4), i + process->ptr);
			// ft_memcpy(arg[a].arg, &map->map[i + process->ptr], inc = (op_tab[process->op - 1].need_c) ? 2 : 4);
		else if (arg[a].type == IND_CODE)
			bidir_memcpy(arg[a].arg, map->map, inc = -T_DIR, i + process->ptr);
			// ft_memcpy(arg[a].arg, &map->map[i + process->ptr], inc = 2);
		else
			break ;
		arg[a++].len = (size_t)-inc;
		i += (int)-inc;
		translation++;
	}
	arg[a].type = 0;
	return (arg);
}

unsigned	*tabarg(t_arg *arg, int *inc, t_map *map, t_process *process)
{
	static unsigned	param[3];
	short		cast;
	size_t	a;
	size_t	i;

	a = 0;
	i = 1;
	*inc = (op_tab[process->op - 1].mod_c) ? 1 : 0;
	ft_bzero(param, sizeof(unsigned) * 3);
	while (arg[a].type)
	{
		if (arg[a].type == REG_CODE)
			param[a] = (*arg[a].arg) - 1;
		else if (arg[a].type == DIR_CODE || process->op == 3)
		{
			param[a] = (op_tab[process->op - 1].need_c) ? (short)ft_short_endian_swap((unsigned short*)arg[a].arg) :
			(int)ft_endian_swap((unsigned *)arg[a].arg);
			// printf("Got direct arg: %hi for op = %s\n", (short)(*(short*)(arg[a].arg)), op_tab[process->op - 1].name);
		}
		else if (arg[a].type == IND_CODE) {
			cast = (short)ft_short_endian_swap((unsigned short *)arg[a].arg);
			// printf("Got indirect arg: %hi for op = %s\n", cast, op_tab[process->op - 1].name);
			if (process->op < 13)
				cast %= IDX_MOD;
			cast = cast < 0 ? MEM_SIZE + cast : cast;
			cast = cast >= MEM_SIZE ? cast - MEM_SIZE : cast;
			bidir_memcpy(&param[a], map->map, -REG_SIZE, process->ptr + cast);
			// ft_memcpy(&param[a], &map->map[(process->ptr + cast) % MEM_SIZE], REG_SIZE);
		}
		*inc += arg[a].len;
		a++;
	}
	return (param);
}

/*
* Si n est negatif, alors on copie depuis la map,
* sinon, on copie dans la map.
*/


int	live(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	unsigned char	tmp[4];
	unsigned		*cast;

	(void)allprocess;
	// ft_memmove(tmp, &map->map[process->ptr + 1], 4);
	bidir_memcpy(&tmp, map->map, -REG_SIZE, process->ptr + 1);
	cast = (unsigned *)tmp;
	ft_endian_swap(cast);
	if (LIFECODE - *cast >= champslen(champ))
		return (4);
	champ[LIFECODE - *cast].lastlife = map->t_cycles;
	process->life = CYCLE_TO_DIE - CYCLE_DELTA * map->round;
	map->lives++;
	return (4); // Return 4: constant size of live parameter.
}

int	ld(t_map *map, t_champ *champ, t_process *process, t_list **allprocess) // RAJOUTER EN FONCTION DU IDX MOD
{
	t_arg				*arg;
	int					inc;
	int					*param;

	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	if (process->op < 13 && arg[0].type == DIR_CODE)
		ft_endian_swap((unsigned *)&param[0]);
	ft_memcpy(&process->reg[REG_SIZE * param[1]], &param[0], REG_SIZE);
	process->carry = param[0] ? 0 : 1;
	return (inc);
}

int	st(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg				*arg;
	int					inc;
	int					*param;
	short				cast;

	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	if (arg[1].type == T_REG)
		ft_memcpy(&process->reg[param[1] * REG_SIZE], &process->reg[param[0] * REG_SIZE], REG_SIZE);
	else
	{
		// printf("Param is a direct with:\n	ORIGINAL: %x\n", param[1]);
		// printf("short: %hi\n", (short)param[1]);
		cast = (short)param[1] % (short)IDX_MOD + process->ptr;
		cast = cast < 0 ? MEM_SIZE + cast : cast;
		cast = cast >= MEM_SIZE ? cast - MEM_SIZE : cast;
		// printf("cast at : %i\n", cast);
		// ft_memcpy(&map->map[cast], &process->reg[param[0] * REG_SIZE], REG_SIZE);
		// ft_memset(&map->c_map[cast], (int)process->champ->num + 1, REG_SIZE);
		// printf("num_reg = %i | reg = %p | cast = %hi\n", param[0], &process->reg[param[0] * REG_SIZE], cast);
		bidir_memcpy(map->map, &process->reg[param[0] * REG_SIZE], REG_SIZE, cast);
		// ft_memset(&map->c_map[cast], (int)process->champ->num + 1, REG_SIZE);
		bidir_memset(map->c_map, process->champ->num + 1, REG_SIZE, cast);
	}
	process->carry = (short)param[0] ? 1 : 0;
	return (inc);
}

int	add(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg			*arg;
	int				inc;
	unsigned int	*param;
	int				nb[2];
	int				tmp;


	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (unsigned int*)tabarg(arg, &inc, map, process);
	nb[0] = (int)(*((int*)&process->reg[REG_SIZE * param[0]]));
	nb[1] = (int)(*((int*)&process->reg[REG_SIZE * param[1]]));
	tmp = nb[0] + nb[1];
	ft_memcpy(&process->reg[REG_SIZE * param[2]], &tmp, REG_SIZE);
	process->carry = tmp ? 0 : 1;
	return (inc);
}

int	sub(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg			*arg;
	int				inc;
	unsigned int	*param;
	int				nb[2];
	int				tmp;


	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (unsigned int*)tabarg(arg, &inc, map, process);
	nb[0] = (int)(*((int*)&process->reg[REG_SIZE * param[0]]));
	nb[1] = (int)(*((int*)&process->reg[REG_SIZE * param[1]]));
	tmp = nb[0] - nb[1];
	ft_memcpy(&process->reg[REG_SIZE * param[2]], &tmp, REG_SIZE);
	process->carry = tmp ? 0 : 1;
	return (inc);
}

int	and(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg	*arg;
	int		inc;
	int		*param;
	int		tmp;
	int 	cast;

	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	cast = (int)ft_endian_swap((unsigned *)&param[0]);
	tmp =  ((arg[0].type == IND_CODE) ? cast : param[0]) & param[1];
	tmp = (arg[0].type == IND_CODE) ? (int)ft_endian_swap((unsigned *)&tmp) : tmp;
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (tmp) ? 0 : 1;
	return (inc);
}

int	or(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg	*arg;
	int		inc;
	int		*param;
	int		tmp;
	int 	cast;

	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	cast = (int)ft_endian_swap((unsigned *)&param[0]);
	tmp =  ((arg[0].type == IND_CODE) ? cast : param[0]) | param[1];
	tmp = (arg[0].type == IND_CODE) ? (int)ft_endian_swap((unsigned *)&tmp) : tmp;
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (tmp) ? 0 : 1;
	return (inc);
}

int	xor(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg	*arg;
	int		inc;
	int		*param;
	int		tmp;
	int 	cast;

	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	cast = (int)ft_endian_swap((unsigned *)&param[0]);
	tmp =  ((arg[0].type == IND_CODE) ? cast : param[0]) ^ param[1];
	tmp = (arg[0].type == IND_CODE) ? (int)ft_endian_swap((unsigned *)&tmp) : tmp;
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (tmp) ? 0 : 1;
	return (inc);
}

int	zjmp(t_map *map, t_champ *champ, t_process *process, t_list **allprocess) // TODO: Handle map loops
{
	unsigned short	param;

	(void)champ;
	(void)allprocess;
	ft_memcpy(&param, &map->map[(process->ptr + 1) % MEM_SIZE], sizeof(unsigned short));
	ft_short_endian_swap(&param);
	if (process->carry)
		return ((short)param - 1);
	return (2);
}

int	ldi(t_map *map, t_champ *champ, t_process *process, t_list **allprocess) // Faire les additions des registres
{
	t_arg				*arg;
	int					inc;
	int					*param;
	int					tmp;
	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	if (arg[0].type == T_REG)
		param[0] = process->reg[REG_SIZE * param[0]] % ((process->op < 13) ? IDX_MOD : MEM_SIZE);
	if (arg[1].type == T_REG)
		param[1] = process->reg[REG_SIZE * param[1]] % ((process->op < 13) ? IDX_MOD : MEM_SIZE);
	tmp = (param[0] + param[1]) % IDX_MOD + process->ptr;
	tmp = tmp < 0 ? MEM_SIZE + tmp : tmp;
	tmp = tmp >= MEM_SIZE ? tmp - MEM_SIZE : tmp;
	// ft_memcpy(&process->reg[REG_SIZE * param[2]], &map->map[tmp], REG_SIZE);
	bidir_memcpy(&process->reg[REG_SIZE * param[2]], map->map, -REG_SIZE, tmp);
	return (inc);
}

int	sti(t_map *map, t_champ *champ, t_process *process, t_list **allprocess) // memcpy rot
{
	t_arg				*arg;
	int					inc;
	int					*param;
	int					*cast;
	int					tmp;

	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	if (arg[1].type == T_REG && (cast = (int *)&process->reg[REG_SIZE * param[1]]))
		param[1] = *cast;
	if (arg[2].type == T_REG && (cast = (int *)&process->reg[REG_SIZE * param[2]]))
		param[2] = *cast;
	tmp = (param[1] + param[2]) % IDX_MOD + process->ptr;
	// printf("pos : %i - TMP = %hi avec %hi + %hi\n", process->ptr, (short)tmp, (short)param[1], (short)param[2]);
	tmp = tmp < 0 ? MEM_SIZE + tmp : tmp;
	tmp = tmp >= MEM_SIZE ? tmp - MEM_SIZE : tmp;
	// ft_memcpy(&map->map[tmp], &process->reg[param[0] * REG_SIZE], REG_SIZE);
	// ft_memset(&map->c_map[tmp], process->champ->num + 1, REG_SIZE);
	bidir_memcpy(map->map, &process->reg[param[0] * REG_SIZE], REG_SIZE, tmp);
	bidir_memset(map->c_map, process->champ->num + 1, REG_SIZE, tmp);
	return (inc);
}

int	cfork(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_process	*tmp;
	short		k;
	short		*cast;

	(void)map;
	(void)champ;
	if (!(tmp = proccpy(&process)))
		exit (1);
	ft_memmove(&k, &map->map[(process->ptr + 1) % MEM_SIZE], 2);
	cast = &k;
	ft_short_endian_swap((unsigned short*)cast);
	tmp->ptr += (*cast % IDX_MOD);
	tmp->ptr %= MEM_SIZE;
	tmp->ptr = tmp->ptr >= MEM_SIZE ? tmp->ptr - MEM_SIZE : tmp->ptr;
	tmp->life--;
	ft_lstadd(allprocess, ft_lstlink(tmp, sizeof(t_process)));
	return (2);
}

int	lcfork(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_process	*tmp;
	short		k;
	short		*cast;

	(void)map;
	(void)champ;
	if (!(tmp = proccpy(&process)))
		exit (1);
	ft_memmove(&k, &map->map[(process->ptr + 1) % MEM_SIZE], 2);
	cast = &k;
	ft_short_endian_swap((unsigned short*)cast);
	tmp->ptr += *cast;
	tmp->ptr %= MEM_SIZE;
	tmp->ptr = tmp->ptr >= MEM_SIZE ? tmp->ptr - MEM_SIZE : tmp->ptr;
	tmp->life--;
	ft_lstadd(allprocess, ft_lstlink(tmp, sizeof(t_process)));
	return (2);
}

int aff(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg				*arg;
	int					*param;
	int					inc;
	(void)champ;
	(void)allprocess;

	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	ft_printf("%c\n", (char)(param[0] % 256));
	return (2);
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

	if (map->map[process->ptr] < 17 && process->active
	&& !process->cycles && process->op)
	{
		toadd = f[(size_t)process->op - 1](map, champs, process, allprocess);
		// if (process->op == 9)
			// printf("Jumped from %i to %i with jump of %i\n", process->ptr, process->ptr + toadd, toadd);
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

	map->cycles = CYCLE_TO_DIE;
	map->t_cycles = 0;
	map->round = 0;
	map->checks = 0;
	if (r->win) {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glfwSetWindowUserPointer(r->win, r);
	}
	while ((champ_isalive(map, *allprocess, champs))
	|| (r->win && !glfwWindowShouldClose(r->win))) // // Doit rester dans cet ordre
	{
		while (r->pause)
			render(r, map);
		tmp = *allprocess;
		while (tmp && (int)(CYCLE_TO_DIE - CYCLE_DELTA * map->round) > 0) {
			process = (t_process *)tmp->content;
			f_ptr = process->ptr;
			init_action(process, map);
			launch_action(process, map, champs, allprocess);
			if (!process->active && !process->cycles)
				process->ptr++;
			process->life -= (process->life > 0) ? 1 : 0;
			process->ptr = process->ptr < 0 ? MEM_SIZE + process->ptr : process->ptr;
			process->ptr = process->ptr >= MEM_SIZE ? process->ptr - MEM_SIZE : process->ptr;
			map->p_map[f_ptr] = 0;
			map->p_map[process->ptr] = 1;
			tmp = tmp->next;
		}
		if (!map->cycles)
		{
			*allprocess = ft_lstfilter(*allprocess, NULL, &proc_isalive, &delprocess);
			map->cycles = (map->lives >= NBR_LIVE || map->checks == MAX_CHECKS) ?
			CYCLE_TO_DIE - CYCLE_DELTA * ++map->round :
			CYCLE_TO_DIE - CYCLE_DELTA * map->round;
			if (map->lives >= NBR_LIVE || map->checks++ == MAX_CHECKS)
				map->checks = 0;
			if (map->cycles < 0)
				map->cycles = 0;
			map->lives = 0;
		}
		if (r->win && !(map->t_cycles % r->skip))
			render(r, map);
	}
}
