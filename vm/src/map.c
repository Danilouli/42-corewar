#include "corewar.h"

void	setmap(t_map *map, t_champ *champs, t_list *allprocess)
{
	size_t	j;
	size_t	i;
	size_t	c;
	size_t	interval;

	interval = MEM_SIZE / champslen(champs);
	i = 0;
	while (i < champslen(champs))
	{
		ft_memmove(&map->map[i * interval], champs[i].prog, champs[i].len_prog);
		((t_process *)allprocess->content)->ptr = i * interval;
		j = i * interval;
		c = j;
		while (j < c + champs[i].len_prog) {
			map->c_map[j++] = champs[i].num + 1;
		}
		i++;
	}
}
