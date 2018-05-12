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

int		OCPCheck(t_map *map, t_process *process)
{
	unsigned char	*translate;
	unsigned char	res[4];
	int				i;

	i = 0;
	translate = translate_OCP(map->map[(process->ptr + 1) % MEM_SIZE]);
	ft_bzero(res, 4);
	while (i < op_tab[process->op - 1].nb_p)
	{
		if (!translate[i])
			return (0);
		res[i] = 1 << translate[i];
		res[i] >>= 1;
		i++;
	}
	i = 0;
	while (i < op_tab[process->op - 1].nb_p)
	{
		if (!(res[i] & op_tab[process->op - 1].param[i]))
			return (0);
		i++;
	}
	return (1);
}

t_arg	*get_arg(t_map *map, t_process *process, int nbarg, int *in)
{
	size_t			a;
	unsigned char	OCP;
	unsigned char	*translation;
	static t_arg	arg[4];
	int				inc;

	*in = 1;
	(void)nbarg;
	ft_bzero(arg, sizeof(t_arg) * 4);
	OCP = map->map[(*in + process->ptr) % MEM_SIZE];
	translation = translate_OCP(OCP);
	*in += (op_tab[process->op - 1].mod_c) ? 1 : 0;
	a = 0;
	while (a < (size_t)op_tab[process->op - 1].nb_p)
	{
		ft_bzero(arg[a].arg, 4);
		inc = 0;
		if (!(arg[a].type = *translation))
			return (arg);
		if (arg[a].type == REG_CODE)
			bidir_memcpy(arg[a].arg, map->map, inc = -T_REG, *in + process->ptr);
		else if (arg[a].type == DIR_CODE || (process->op == 3 && arg[a].type == IND_CODE))
			bidir_memcpy(arg[a].arg, map->map, inc = -((op_tab[process->op - 1].need_c || (process->op == 3 && arg[a].type == IND_CODE)) ? 2 : 4), *in + process->ptr);
		else if (arg[a].type == IND_CODE)
			bidir_memcpy(arg[a].arg, map->map, inc = -T_DIR, *in + process->ptr);
		else
		{
			*in = *in - 1;
			return (NULL);
		}
		arg[a++].len = (size_t)-inc;
		*in -= (int)inc;
		translation++;
	}
	arg[a].type = 0;
	*in = *in - 1;
	// printf("OP: %s | in: %i\n", op_tab[process->op - 1].name, *in);
	return (arg);
}

unsigned	*tabarg(t_arg *arg, t_map *map, t_process *process)
{
	static unsigned	param[3];
	short			cast;
	size_t			a;
	size_t			i;

	a = 0;
	i = 1;
	ft_bzero(param, sizeof(unsigned) * 3);
	if (!arg || !OCPCheck(map, process))
		return (0);
	while (a < (size_t)op_tab[process->op - 1].nb_p)
	{
		if (arg[a].type == REG_CODE && *arg[a].arg > 0 && *arg[a].arg <= REG_NUMBER)
			param[a] = (*arg[a].arg) - 1;
		else if (arg[a].type == DIR_CODE || (process->op == 3 && arg[a].type == IND_CODE))
		{
			param[a] = (op_tab[process->op - 1].need_c || (process->op == 3 && arg[a].type == IND_CODE)) ? (short)ft_short_endian_swap((unsigned short*)arg[a].arg) :
			(int)ft_endian_swap((unsigned *)arg[a].arg);
			// printf("Got direct arg: %hi for op = %s\n", (short)(*(short*)(arg[a].arg)), op_tab[process->op - 1].name);
		}
		else if (arg[a].type == IND_CODE)
		{
			cast = (short)ft_short_endian_swap((unsigned short *)arg[a].arg);
			// printf("Got indirect arg: %hi for op = %s\n", cast, op_tab[process->op - 1].name);
			if (process->op < 13)
				cast %= IDX_MOD;
			cast = cast < 0 ? MEM_SIZE + cast : cast;
			cast = cast >= MEM_SIZE ? cast - MEM_SIZE : cast;
			bidir_memcpy(&param[a], map->map, -REG_SIZE, process->ptr + cast);
			// ft_memcpy(&param[a], &map->map[(process->ptr + cast) % MEM_SIZE], REG_SIZE);
		}
		else
			return (NULL);
		a++;
	}
	return (param);
}
