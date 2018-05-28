/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:09:16 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/28 17:09:17 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	nb[0] = (int)(*((int*)&process->reg[RS * param[0]]));
	nb[1] = (int)(*((int*)&process->reg[RS * param[1]]));
	ft_endian_swap((unsigned*)&nb[0]);
	ft_endian_swap((unsigned*)&nb[1]);
	tmp = nb[0] + nb[1];
	ft_endian_swap((unsigned*)&tmp);
	ft_memcpy(&process->reg[RS * param[2]], &tmp, RS);
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
	nb[0] = (int)(*((int*)&process->reg[RS * param[0]]));
	nb[1] = (int)(*((int*)&process->reg[RS * param[1]]));
	ft_endian_swap((unsigned*)&nb[0]);
	ft_endian_swap((unsigned*)&nb[1]);
	tmp = nb[0] - nb[1];
	ft_endian_swap((unsigned*)&tmp);
	ft_memcpy(&process->reg[RS * param[2]], &tmp, RS);
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
	assign_param(param, arg, process);
	tmp = param[0] & param[1];
	ft_endian_swap((unsigned *)&tmp);
	ft_memcpy(&process->reg[RS * param[2]], &tmp, RS);
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
	assign_param(param, arg, process);
	tmp = param[0] | param[1];
	ft_endian_swap((unsigned *)&tmp);
	ft_memcpy(&process->reg[RS * param[2]], &tmp, RS);
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
	assign_param(param, arg, process);
	tmp = param[0] ^ param[1];
	ft_endian_swap((unsigned *)&tmp);
	ft_memcpy(&process->reg[RS * param[2]], &tmp, RS);
	process->carry = (tmp) ? 0 : 1;
	return (inc);
}
