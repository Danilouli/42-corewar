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
	if (LIFECODE - *cast >= champslen(champ))
		return ;
	champ[LIFECODE - *cast].lastlife = map->cycles;
	process->life = CYCLE_TO_DIE;
}

void	process_operations(t_map *map, t_champ *champs, t_list **allprocess)
{
	t_list	*tmp;
	intmax_t	cycles;

	(void)map;
	(void)champs;
	cycles = 0;
	while (champ_isalive(cycles, *allprocess, champs))
	{
		tmp = *allprocess;
		while (tmp)
		{
			ft_printf("champ : %s > %lli\n", ((t_process *)tmp->content)->champ->name, cycles - ((t_process *)tmp->content)->champ->lastlife);
			((t_process *)tmp->content)->life--;
			tmp = tmp->next;
		}
		if (!(cycles % CYCLE_TO_DIE))
			*allprocess = ft_lstfilter(*allprocess, NULL, &proc_isalive, &delprocess);
		cycles++;
	}
}
