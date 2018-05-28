/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:58:06 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/28 14:58:07 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	*translate_ocp(unsigned char ocp)
{
	int						i;
	unsigned char			mask;
	static unsigned char	res[4];

	i = -1;
	mask = 3;
	ft_bzero(res, 4);
	while (++i < 3)
		res[i] = ocp >> (6 - (i * 2)) & mask;
	return (res);
}

int				ocpcheck(t_map *map, t_process *process)
{
	unsigned char	*translate;
	unsigned char	res[4];
	int				i;

	i = -1;
	translate = translate_ocp(map->map[(process->ptr + 1) % MEM_SIZE]);
	ft_bzero(res, 4);
	while (++i < op_tab[process->op - 1].nb_p)
	{
		if (!translate[i])
			return (0);
		res[i] = 1 << translate[i];
		res[i] >>= 1;
	}
	i = -1;
	while (++i < op_tab[process->op - 1].nb_p)
		if (!(res[i] & op_tab[process->op - 1].param[i]))
			return (0);
	return (1);
}
