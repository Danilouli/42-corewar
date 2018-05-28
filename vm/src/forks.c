/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:46:37 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/28 15:46:39 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	cfork(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_process	*tmp;
	short		k;
	short		*cast;

	(void)map;
	(void)champ;
	tmp = proccpy(&process);
	bidir_memcpy(&k, map->map, -2, process->ptr + 1);
	cast = &k;
	ft_short_endian_swap((unsigned short*)cast);
	tmp->ptr += (*cast % IDX_MOD);
	tmp->ptr %= MEM_SIZE;
	tmp->ptr = tmp->ptr >= MEM_SIZE ? tmp->ptr - MEM_SIZE : tmp->ptr;
	tmp->life--;
	ft_lstadd(allprocess, ft_lstlink(tmp, sizeof(t_process)));
	return (2);
}

int	lcfork(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_process	*tmp;
	short		k;
	short		*cast;

	(void)map;
	(void)champ;
	tmp = proccpy(&process);
	bidir_memcpy(&k, map->map, -2, process->ptr + 1);
	cast = &k;
	ft_short_endian_swap((unsigned short*)cast);
	tmp->ptr += *cast;
	tmp->ptr %= MEM_SIZE;
	tmp->ptr = tmp->ptr >= MEM_SIZE ? tmp->ptr - MEM_SIZE : tmp->ptr;
	tmp->life--;
	ft_lstadd(allprocess, ft_lstlink(tmp, sizeof(t_process)));
	return (2);
}
