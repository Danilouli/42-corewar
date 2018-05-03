#include "corewar.h"

int	st(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg				*arg;
	int					inc;
	int					*param;
	short				cast;

	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	if (arg[1].type == T_REG)
		ft_memcpy(&process->reg[param[1] * REG_SIZE], &process->reg[param[0] * REG_SIZE], REG_SIZE);
	else
	{
		cast = (short)param[1] % (short)IDX_MOD + process->ptr;
		cast = cast < 0 ? MEM_SIZE + cast : cast;
		cast = cast >= MEM_SIZE ? cast - MEM_SIZE : cast;
		bidir_memcpy(map->map, &process->reg[param[0] * REG_SIZE], REG_SIZE, cast);
		bidir_memset(map->c_map, process->champ->num + 1, REG_SIZE, cast);
	}
	process->carry = (short)param[0] ? 1 : 0;
	return (inc);
}


int	sti(t_map *map, t_champ *champ, t_process *process, t_list **allprocess) // memcpy rot
{
	t_arg				*arg;
	int					inc;
	int					*param;
	int					tmp;

	(void)champ;
	(void)allprocess;
	if (!(arg = get_arg(map, process, op_tab[process->op - 1].nb_p)))
		return (op_tab[process->op - 1].nb_p - 1);
	param = (int*)tabarg(arg, &inc, map, process);
	if (arg[1].type == REG_CODE)
	{
		tmp = (int)*(int *)&process->reg[REG_SIZE * param[1]];
		param[1] = (int)(ft_endian_swap((unsigned *)&tmp));
	}
	if (arg[2].type == REG_CODE)
	{
		tmp = (int)*(int *)&process->reg[REG_SIZE * param[2]];
		param[2] = (int)(ft_endian_swap((unsigned *)&tmp));
	}
	if (arg[1].type == IND_CODE)
		param[1] = (int)(ft_endian_swap((unsigned *)&param[1]));
	if (arg[2].type == IND_CODE)
		param[2] = (int)(ft_endian_swap((unsigned *)&param[2]));
	tmp = (param[1] + param[2]) % IDX_MOD + process->ptr;
	tmp = tmp < 0 ? MEM_SIZE + tmp : tmp;
	tmp = tmp >= MEM_SIZE ? tmp - MEM_SIZE : tmp;
	bidir_memcpy(map->map, &process->reg[param[0] * REG_SIZE], REG_SIZE, tmp);
	bidir_memset(map->c_map, process->champ->num + 1, REG_SIZE, tmp);
	return (inc);
}