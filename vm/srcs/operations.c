#include "corewar.h"

void	live(t_map *map, t_champ *champ, t_process *process)
{
	char	tmp[4];
	unsigned	*cast;

	(void)map;
	(void)champ;
	ft_memmove(tmp, process->ptr + 1, 4);
	cast = (unsigned *)tmp;
	ft_endian_swap(cast);
	if (LIFECODE - *cast >= MAX_PLAYERS)
		return ;
	champ[LIFECODE - *cast].lastlife = map->cycles;
	process->life = CYCLE_TO_DIE;
}
