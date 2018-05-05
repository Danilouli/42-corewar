#include "corewar.h"

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

int	live(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	unsigned char	tmp[4];
	unsigned		*cast;

	(void)allprocess;
	// ft_memmove(tmp, &map->map[process->ptr + 1], 4);
	bidir_memcpy(&tmp, map->map, -REG_SIZE, process->ptr + 1);
	cast = (unsigned *)tmp;
	ft_endian_swap(cast);
	process->life = CYCLE_TO_DIE - CYCLE_DELTA * map->round;
	if (LIFECODE - *cast >= champslen(champ))
		return (4);
	champ[LIFECODE - *cast].lastlife = map->t_cycles;
	map->lives++;
	return (4); // Return 4: constant size of live parameter.
}
