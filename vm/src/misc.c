/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:18:41 by fsabatie          #+#    #+#             */
/*   Updated: 2018/04/17 22:55:45 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <math.h>

void	*retin(int *in)
{
	*in = *in - 1;
	return (NULL);
}

void	prt_map_hex(t_map map)
{
	size_t			i;
	unsigned char	*hex;

	hex = map.map;
	i = 0;
	while (i < MEM_SIZE)
	{
		if (map.p_map[i] == 1)
			ft_printf("\x1b[35m");
		else if (map.c_map[i] == 1)
			ft_printf("\x1b[31m");
		else if (map.c_map[i] == 2)
			ft_printf("\x1b[32m");
		else if (map.c_map[i] == 3)
			ft_printf("\x1b[33m");
		else if (map.c_map[i] == 4)
			ft_printf("\x1b[34m");
		else if (map.c_map[i] == 0)
			ft_printf("\x1b[39m");
		ft_printf("%02x", hex[i++]);
		ft_printf("\x1b[39m");
		(i % 64 == 0) ? ft_putchar('\n') : ft_putchar(' ');
	}
	printf("Cycles at : %li\n", map.t_cycles);
}

size_t	champslen(t_champ *champs)
{
	size_t	i;

	i = 0;
	while (champs[i].num >= 0)
		i++;
	return (i);
}

void	assign_param(int *param, t_arg *arg, t_process *p)
{
	int tmp;

	if (arg[0].type == RC)
	{
		tmp = (int)*(int *)&p->reg[RS * param[0]];
		param[0] = (int)(ft_endian_swap((unsigned *)&tmp));
	}
	if (arg[1].type == RC)
	{
		tmp = (int)*(int *)&p->reg[RS * param[1]];
		param[1] = (int)(ft_endian_swap((unsigned *)&tmp));
	}
	if (arg[0].type == IC)
		param[0] = (int)(ft_endian_swap((unsigned *)&param[0]));
	if (arg[1].type == IC)
		param[1] = (int)(ft_endian_swap((unsigned *)&param[1]));
}

float	interpolation(short n, float points[][3], float x, float y)
{
	short i;
	float polynome;
	float f;
	float s;

	i = 0;
	polynome = 0;
	while (i < n)
	{
		f = (float)powf(x - points[i][0], 2);
		s = (float)powf(y - points[i][1], 2);
		polynome += (float)points[i][2] * 2 * pow(2, -(f + s) * 0.2);
		i++;
	}
	return (polynome);
}
