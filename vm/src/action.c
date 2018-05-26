#include "corewar.h"

static inline void 	init_action(t_process *process, t_map *map)
{
	if (!process->active && map->map[process->ptr] > 0 && map->map[process->ptr] < 17)
	{
		process->op = map->map[process->ptr];
		process->cycles = op_tab[map->map[process->ptr] - 1].cycles;
		process->active = 1;
	}
	process->cycles -= (process->active) ? 1 : 0;
}

static inline void 	launch_action(t_process *process, t_map *map, t_champ *champs, \
					t_list **allprocess)
{
	int toadd = 0;
	static	int	(*f[17])(t_map *, t_champ *, t_process *, t_list **allprocess) = {
		&live, &ld, &st, &add, &sub, &and, &or, &xor, &zjmp, &ldi, &sti, &cfork,
		&ld, &ldi, &lcfork, &aff, NULL
	};

	if (process->active && !process->cycles && process->op)
	{
		toadd = f[(size_t)process->op - 1](map, champs, process, allprocess);
		process->ptr += toadd;
		process->ptr = (process->ptr < 0) ? MEM_SIZE + process->ptr : process->ptr;
		process->op = 0;
		process->active = 0;
	}
}

void	processit(t_map *map, t_list **allprocess, t_champ *champs, t_process *process)
{
	int			f_ptr;

	f_ptr = process->ptr;
	init_action(process, map);
	launch_action(process, map, champs, allprocess);
	if (!process->active && !process->cycles)
		process->ptr++;
	process->life--;
	process->ptr = process->ptr < 0 ? MEM_SIZE + process->ptr : process->ptr;
	process->ptr = process->ptr >= MEM_SIZE ? process->ptr - MEM_SIZE : process->ptr;
	map->p_map[f_ptr] = 0;
	map->p_map[process->ptr] = 1;
}
