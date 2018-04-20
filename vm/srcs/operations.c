#include "corewar.h"

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

t_arg	*get_arg(t_map *map, t_process *process)
{
	size_t			a;
	size_t			i;
	unsigned char	OCP;
	unsigned char	*translation;
	static t_arg	arg[4];
	size_t			inc;

	i = 1;
	ft_bzero(arg, sizeof(t_arg) * 4);
	OCP = map->map[i + process->ptr < MEM_SIZE ? i + process->ptr : 0];
	translation = (op_tab[process->op - 1].mod_c) ? translate_OCP(OCP) : NULL;
	i += (op_tab[process->op - 1].mod_c) ? 1 :0;
	a = 0;
	while (*translation)
	{
		ft_bzero(arg[a].arg, 4);
		inc = 0;
		arg[a].type = *translation;
		if (arg[a].type == REG_CODE)
			ft_memcpy(arg[a].arg, &map->map[i + process->ptr], inc = T_REG);
		else if (arg[a].type == DIR_CODE)
			ft_memcpy(arg[a].arg, &map->map[i + process->ptr], inc = (op_tab[process->op - 1].need_c) ? T_DIR : T_DIR * 2);
		else if (arg[a].type == IND_CODE)
			ft_memcpy(arg[a].arg, &map->map[i + process->ptr], inc = T_IND);
		else
			break ;
		arg[a++].len = inc;
		i += inc;
		translation++;
	}
	arg[a].type = 0;
	return (arg);
}

unsigned	*tabarg(t_arg *arg, size_t *inc, t_map *map, t_process *process)
{
	static unsigned	param[3];
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
		else if (arg[a].type == DIR_CODE)
		{
			param[a] = (op_tab[process->op - 1].need_c) ? (unsigned)ft_short_endian_swap((unsigned short*)arg[a].arg) :
			ft_endian_swap((unsigned *)arg[a].arg);
			// printf("Param: %u\n", *arg[a].arg);
		}
		else if (arg[a].type == IND_CODE) {
			param[a] = ft_endian_swap((unsigned int *)arg[a].arg);
			ft_memcpy(&param[a], &map->map[process->ptr + param[a]], REG_SIZE);
		}
		*inc += arg[a].len;
		a++;
	}
	return (param);
}

void	*memcpyrot(void *dst, void *src, size_t n, size_t where)
{
	unsigned char	*s;
	unsigned char	*d;

	s = src;
	d = dst;
	while (where < MEM_SIZE && n)
	{
		d[where] = *s;
		if (++where == MEM_SIZE)
			where = 0;
		n--;
		s++;
	}
	return dst;
}

size_t	live(t_map *map, t_champ *champ, t_process *process)
{
	unsigned char	tmp[4];
	unsigned		*cast;

	process->active = 1;
	ft_memmove(tmp, &map->map[process->ptr + 1], 4);
	cast = (unsigned *)tmp;
	ft_endian_swap(cast);
	if (LIFECODE - *cast >= champslen(champ))
		return (0);
	champ[LIFECODE - *cast].lastlife = map->cycles;
	process->life = CYCLE_TO_DIE;
	return (4); // Return 4: constant size of live parameter.
}

size_t	zjmp(t_map *map, t_champ *champ, t_process *process)
{
	t_arg				*arg;
	size_t				inc;
	unsigned			*param;
	unsigned			tmp;

	(void)champ;
	arg = get_arg(map, process);
	param = tabarg(arg, &inc, map, process);
	if (!process->carry) {
		process->ptr += param[0] % IDX_MOD;
		process->ptr %= MEM_SIZE;
	}
	return (inc);
}

size_t	xor(t_map *map, t_champ *champ, t_process *process)
{
	t_arg				*arg;
	size_t				inc;
	unsigned			*param;
	unsigned			tmp;

	(void)champ;
	arg = get_arg(map, process);
	param = tabarg(arg, &inc, map, process);
	tmp = param[0] ^ param[1];
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (param[0] ^ param[1]) ? 1 : 0;
	return (inc);
}

size_t	or(t_map *map, t_champ *champ, t_process *process)
{
	t_arg				*arg;
	size_t				inc;
	unsigned			*param;
	unsigned			tmp;

	(void)champ;
	arg = get_arg(map, process);
	param = tabarg(arg, &inc, map, process);
	tmp = param[0] | param[1];
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (param[0] | param[1]) ? 1 : 0;
	return (inc);
}

size_t	sub(t_map *map, t_champ *champ, t_process *process)
{
	t_arg				*arg;
	size_t				inc;
	unsigned			*param;
	unsigned			tmp;

	(void)champ;
	arg = get_arg(map, process);
	param = tabarg(arg, &inc, map, process);
	tmp = process->reg[REG_SIZE * param[0]] - process->reg[REG_SIZE * param[1]]
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (param[0] - param[1]) ? 1 : 0;
	return (inc);
}

size_t	add(t_map *map, t_champ *champ, t_process *process)
{
	t_arg				*arg;
	size_t				inc;
	unsigned			*param;
	unsigned			tmp;

	(void)champ;
	arg = get_arg(map, process);
	param = tabarg(arg, &inc, map, process);
	tmp = process->reg[REG_SIZE * param[0]] + process->reg[REG_SIZE * param[1]]
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (param[0] + param[1]) ? 1 : 0;
	return (inc);
}

size_t	and(t_map *map, t_champ *champ, t_process *process)
{
	t_arg				*arg;
	size_t				inc;
	unsigned			*param;
	unsigned			tmp;

	(void)champ;
	arg = get_arg(map, process);
	param = tabarg(arg, &inc, map, process);
	tmp = param[0] & param[1];
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (param[0] & param[1]) ? 1 : 0;
	return (inc);
}

size_t	ld(t_map *map, t_champ *champ, t_process *process) // RAJOUTER EN FONCTION DU IDX MOD
{
	t_arg				*arg;
	size_t				inc;
	unsigned			*param;

	(void)champ;
	arg = get_arg(map, process);
	param = tabarg(arg, &inc, map, process);
	ft_memcpy(&process->reg[REG_SIZE * param[1]], &param[0], REG_SIZE);
	process->carry = 1;
	return (inc);
}

size_t	sti(t_map *map, t_champ *champ, t_process *process)
{
	t_arg				*arg;
	size_t				inc;
	unsigned			*param;

	(void)champ;
	arg = get_arg(map, process);
	param = tabarg(arg, &inc, map, process);
	ft_memcpy(&map->map[process->ptr + param[1] + param[2]], &process->reg[REG_SIZE * param[0]], REG_SIZE);
	printf("< %i | %i >\n", (int)param[1], (int)param[2]);
	prt_map_hex(*map);
	return (inc);
}

void	process_operations(t_map *map, t_champ *champs, t_list **allprocess)
{
	t_list			*tmp;
	t_process		*process;
	static	size_t	(*f[17])(t_map *, t_champ *, t_process *) = {
		&live, &ld, NULL, &add, &sub, &and, &or, &xor, &zjmp, NULL, &sti, NULL,
		NULL, NULL, NULL, NULL, NULL
	};

	map->cycles = 0;
	while (champ_isalive(map->cycles, *allprocess, champs))
	{
		tmp = *allprocess;
		// ft_printf("CYCLES : %lli\n", cycles);
		while (tmp)
		{
			process = (t_process *)tmp->content;
			if (!process->active && map->map[process->ptr] < 17)
			{
				process->op = map->map[process->ptr];
				process->cycles = op_tab[map->map[process->ptr]].cycles;
				process->active = 1;
			}
			process->cycles--;
			if (map->map[process->ptr] < 17
				&& process->active
				&& !process->cycles
				&& process->op)
				{
					process->ptr += f[(size_t)process->op - 1](map, champs, process);
					process->op = 0;
					process->active = 0;
				}
			if (!process->active && !process->cycles)
				process->ptr++;
			process->life--;
			process->ptr %= MEM_SIZE;
			tmp = tmp->next;
		}
		if (!(++map->cycles % CYCLE_TO_DIE))
			*allprocess = ft_lstfilter(*allprocess, NULL, &proc_isalive, &delprocess);
	}
}
