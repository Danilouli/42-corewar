#include "corewar.h"

void	setmap(t_map *map, t_champ *champs)
{
	size_t	j;
	size_t	i;
	size_t	interval;

	interval = MEM_SIZE / champslen(champs);
	i = 0;
	while (i * interval < MEM_SIZE)
	{
		ft_memmove(&map->map[i * interval], champs[i].prog, champs[i].len_prog);
		j = i * interval;
		while (j < champs[i].len_prog)
			map->owner[j++] = &champs[i];
		i++;
	}
	write(1, map->map, MEM_SIZE);
}
