#include "corewar.h"

int	add(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg			*arg;
	int				inc;
	unsigned int	*param;
	int				nb[2];
	int				tmp;


	(void)champ;
	(void)allprocess;
	arg = get_arg(map, process, op_tab[process->op - 1].nb_p, &inc);
	if (!(param = tabarg(arg, map, process)))
		return (inc);
	nb[0] = (int)(*((int*)&process->reg[REG_SIZE * param[0]]));
	nb[1] = (int)(*((int*)&process->reg[REG_SIZE * param[1]]));
	ft_endian_swap((unsigned*)&nb[0]);
	ft_endian_swap((unsigned*)&nb[1]);
	tmp = nb[0] + nb[1];
	ft_endian_swap((unsigned*)&tmp);
	ft_memcpy(&process->reg[REG_SIZE * param[2]], &tmp, REG_SIZE);
	process->carry = tmp ? 0 : 1;
	return (inc);
}

int	sub(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg			*arg;
	int				inc;
	unsigned int	*param;
	int				nb[2];
	int				tmp;


	(void)champ;
	(void)allprocess;
	arg = get_arg(map, process, op_tab[process->op - 1].nb_p, &inc);
	if (!(param = tabarg(arg, map, process)))
		return (inc);
	nb[0] = (int)(*((int*)&process->reg[REG_SIZE * param[0]]));
	nb[1] = (int)(*((int*)&process->reg[REG_SIZE * param[1]]));
	ft_endian_swap((unsigned*)&nb[0]);
	ft_endian_swap((unsigned*)&nb[1]);
	tmp = nb[0] - nb[1];
	ft_endian_swap((unsigned*)&tmp);
	ft_memcpy(&process->reg[REG_SIZE * param[2]], &tmp, REG_SIZE);
	process->carry = tmp ? 0 : 1;
	return (inc);
}

int	and(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg	*arg;
	int		inc;
	int		*param;
	int		tmp;

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
	tmp = param[0] & param[1];
	ft_endian_swap((unsigned *)&tmp);
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (tmp) ? 0 : 1;
	return (inc);
}

int	or(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg	*arg;
	int		inc;
	int		*param;
	int		tmp;

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
	tmp = param[0] | param[1];
	ft_endian_swap((unsigned *)&tmp);
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (tmp) ? 0 : 1;
	return (inc);
}

int	xor(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_arg	*arg;
	int		inc;
	int		*param;
	int		tmp;

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
	tmp = param[0] ^ param[1];
	ft_endian_swap((unsigned *)&tmp);
	ft_memcpy(&process->reg[REG_SIZE * param[2]],  &tmp, REG_SIZE);
	process->carry = (tmp) ? 0 : 1;
	return (inc);
}
