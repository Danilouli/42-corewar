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
	OCP = map->map[(i + process->ptr) % MEM_SIZE];
	// printf("OCP = %02x for %s\n", OCP, op_tab[process->op - 1].name);

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
		if (arg[a].type == REG_CODE && map->map[(i + process->ptr) % MEM_SIZE] > 0 && map->map[(i + process->ptr) % MEM_SIZE] < REG_NUMBER + 1)
			bidir_memcpy(arg[a].arg, map->map, inc = -T_REG, i + process->ptr);
		else if (arg[a].type == DIR_CODE || (process->op == 3 && arg[a].type == IND_CODE))
			bidir_memcpy(arg[a].arg, map->map, inc = -((op_tab[process->op - 1].need_c) ? 2 : 4), i + process->ptr);
		else if (arg[a].type == IND_CODE)
			bidir_memcpy(arg[a].arg, map->map, inc = -T_DIR, i + process->ptr);
		else
			break ;
		arg[a++].len = (size_t)-inc;
		i -= (int)inc;
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
