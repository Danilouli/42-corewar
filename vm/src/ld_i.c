#include "corewar.h"


int	ld(t_map *map, t_champ *champ, t_process *process, t_list **allprocess) // RAJOUTER EN FONCTION DU IDX MOD
{
	t_arg				*arg;
	int					inc;
	int					*param;

	(void)champ;
	(void)allprocess;
	arg = get_arg(map, process, op_tab[process->op - 1].nb_p, &inc);
	if (!(param = (int*)tabarg(arg, map, process)))
		return (inc);
	if (process->op < 13 && arg[0].type == DIR_CODE)
		ft_endian_swap((unsigned *)&param[0]);
	ft_memcpy(&process->reg[REG_SIZE * param[1]], &param[0], REG_SIZE);
	process->carry = param[0] ? 0 : 1;
	return (inc);
}

int	ldi(t_map *map, t_champ *champ, t_process *process, t_list **allprocess) // Faire les additions des registres
{
	t_arg				*arg;
	int					inc;
	int					*param;
	int					tmp;

	(void)champ;
	(void)allprocess;
	arg = get_arg(map, process, op_tab[process->op - 1].nb_p, &inc);
	if (!(param = (int*)tabarg(arg, map, process)))
		return (inc);
	if (arg[0].type == REG_CODE)
	{
		tmp = (int)*(int *)&process->reg[REG_SIZE * param[0]];
		param[0] = (int)(ft_endian_swap((unsigned *)&tmp));
	}
	if (arg[1].type == REG_CODE)
	{
		tmp = (int)*(int *)&process->reg[REG_SIZE * param[1]];
		param[1] = (int)(ft_endian_swap((unsigned *)&tmp));
	}
	if (arg[0].type == IND_CODE)
		param[0] = (int)(ft_endian_swap((unsigned *)&param[0]));
	if (arg[1].type == IND_CODE)
		param[1] = (int)(ft_endian_swap((unsigned *)&param[1]));
	tmp = process->ptr + (param[0] + param[1]) % ((process->op < 13) ? IDX_MOD : MEM_SIZE);
	tmp = tmp < 0 ? MEM_SIZE + tmp : tmp;
	tmp = tmp >= MEM_SIZE ? tmp - MEM_SIZE : tmp;
	bidir_memcpy(&process->reg[REG_SIZE * param[2]], map->map, -REG_SIZE, tmp);
	if (process->op > 12)
	{
		param = (int *)&process->reg[REG_SIZE * param[2]];
		process->carry = *param ? 0 : 1;
	}
	return (inc);
}
