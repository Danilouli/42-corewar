#include "corewar.h"

void	setmap(t_map *map, t_champ *champs, t_list *allprocess)
{
	size_t	j;
	size_t	i;
	size_t	c;
	size_t	interval;
	t_process	*process;

	interval = MEM_SIZE / champslen(champs);
	i = champslen(champs);
	while (i)
	{
		i--;
		ft_memmove(&map->map[i * interval], champs[i].prog, champs[i].len_prog);
		process = (t_process *)allprocess->content;
		process->ptr = i * interval;
		j = i * interval;
		c = j;
		while (j < c + champs[i].len_prog) {
			map->c_map[j++] = champs[i].num + 1;
		}
		allprocess = allprocess->next;
	}
}
