#include "corewar.h"

void	setmap(t_map *map, t_champ *champs, t_list *allprocess)
{
	size_t	j;
	size_t	i;
	size_t	interval;

	interval = MEM_SIZE / champslen(champs);
	i = 0;
	while (i < champslen(champs))
	{
		ft_memmove(&map->map[i * interval], champs[i].prog, champs[i].len_prog);
		((t_process *)allprocess->content)->ptr = &map->map[i * interval];
		ft_printf("%x\n", *((t_process *)allprocess->content)->ptr);
		j = i * interval;
		while (j < champs[i].len_prog)
			map->owner[j++] = &champs[i];
		i++;
	}
	// write(1, map->map, MEM_SIZE);
	// ft_putchar('\n');
}
