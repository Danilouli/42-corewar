#include "corewar.h"

unsigned char	*translate_OCP(unsigned char OCP)
{
	unsigned char			i;
	unsigned char			mask;
	static unsigned char	res[4];

	i = 0;
	mask = 3;
	ft_bzero(res, 4);
	while (i < 3)
	{
		res[i] = OCP >> (6 - (i * 2)) & mask;
		i++;
	}
	return (res);
}

t_arg	*get_arg(t_map *map, t_process *process, t_op op)
{
	size_t			a;
	size_t			i;
	unsigned char	OCP;
	unsigned char	*translation;
	static t_arg	arg[4];
	size_t			inc;

	i = 1;
	ft_bzero(arg, sizeof(t_arg) * 4);
	translation = (op.mod_c) ?
	translate_OCP(OCP = map->map[i + process->ptr < MEM_SIZE ? i + process->ptr : 0]) : NULL;
	i++;
	a = 0;
	while (*translation)
	{
		ft_bzero(arg[a].arg, 4);
		arg[a].type = *translation;
		if (arg[a].type == REG_CODE)
			ft_memcpy(arg[a].arg, &map->map[i + process->ptr], inc = T_REG);
		else if (arg[a].type == DIR_CODE)
			ft_memcpy(arg[a].arg, &map->map[i + process->ptr], inc = op.need_c ? T_DIR : T_DIR * 2);
		else
			ft_memcpy(arg[a].arg, &map->map[i + process->ptr], inc = T_IND);
		arg[a++].len = inc;
		i += inc;
		translation++;
	}
	arg[a].type = 0;
	return (arg);
}

void	live(t_map *map, t_champ *champ, t_process *process)
{
	unsigned char	tmp[4];
	unsigned		*cast;

	(void)champ;
	process->active = 1;
	ft_memmove(tmp, &map->map[process->ptr + 1], 4);
	cast = (unsigned *)tmp;
	ft_endian_swap(cast);
	ft_printf("PROUT\n");
	if (LIFECODE - *cast >= champslen(champ))
		return ;
	champ[LIFECODE - *cast].lastlife = map->cycles;
	process->life = CYCLE_TO_DIE;
}

void	sti(t_map *map, t_champ *champ, t_process *process)
{
	size_t				a;
	t_arg				*arg;
	size_t				i;
	// unsigned char	*cast;
	unsigned			c1[3];

	(void)champ;
	// ft_printf("PLOUF\n");
	arg = get_arg(map, process, op_tab[10]);
	a = 0;
	i = 1;
	while (arg[a].type)
	{
		if (arg[a].type == T_REG)
			c1[a] = (*arg[a].arg) - 1;
		else if (arg[a].type == T_DIR)
			c1[a] = ft_short_endian_swap((unsigned short *)arg[a].arg);
		else
			c1[a] = ft_endian_swap((unsigned *)arg[a].arg);
		ft_printf("< %u: %x >",arg[a].len, c1[a]);
		ft_putchar('\n');
		a++;
	}
	unsigned	*cast = (unsigned *)&process->reg[REG_SIZE * c1[0]];
	ft_printf("c1: %x | c2: %x | cast = %x | %i\n", c1[1], c1[2], *cast ,process->ptr + c1[1] + c1[2]);
	ft_memcpy(&map->map[process->ptr + c1[1] + c1[2]], &process->reg[REG_SIZE * c1[0]], REG_SIZE);
	// ft_printf("%u | %u\n", *c1, *c2);
	// process->reg[REG_SIZE * *arg[0].arg] = map->map[*c1 + *c2];
}

void	process_operations(t_map *map, t_champ *champs, t_list **allprocess)
{
	t_list			*tmp;
	t_process		*process;
	static	void	(*f[17])(t_map *, t_champ *, t_process *) = {
		&live, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &sti, NULL,
		NULL, NULL, NULL, NULL, NULL
	};

	(void)champs;
	(void)f;
	map->cycles = 0;
	while (champ_isalive(map->cycles, *allprocess, champs))
	{
		tmp = *allprocess;
		// ft_printf("CYCLES : %lli\n", cycles);
		while (tmp)
		{
			process = (t_process *)tmp->content;
			if (!process->active && map->map[process->ptr] && map->map[process->ptr] < 17)
			{
				process->op = map->map[process->ptr];
				process->cycles = op_tab[map->map[process->ptr]].cycles;
				process->active = 1;
			}
			// ft_printf("op : %i\n", process->op);
			if (map->map[process->ptr]
				&& map->map[process->ptr] < 17
				&& process->active
				&& (process->cycles -= (process->cycles) ? 1 : 0))
				f[(size_t)process->op - 1](map, champs, process);
			process->life--;
			if (process->ptr > MEM_SIZE)
				process->ptr -= MEM_SIZE;
			tmp = tmp->next;
		}
		if (!(++map->cycles % CYCLE_TO_DIE))
			*allprocess = ft_lstfilter(*allprocess, NULL, &proc_isalive, &delprocess);
	}
}
