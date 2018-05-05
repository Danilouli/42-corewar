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

void	prt_map_hex(t_map map)
{
	size_t	i;
	unsigned char *hex;

	system("clear");
	hex = map.map;
	i = 0;
	while(i < MEM_SIZE)
	{
		if (map.p_map[i] == 1)
		{
			ft_printf("\x1b[35m");
			ft_printf("%02x", hex[i]);
			ft_printf("\x1b[39m");
		}
		else if (map.c_map[i] == 1)
		{
			ft_printf("\x1b[31m");
			ft_printf("%02x", hex[i]);
			ft_printf("\x1b[39m");
		}
		else if (map.c_map[i] == 2)
		{
			ft_printf("\x1b[32m");
			ft_printf("%02x", hex[i]);
			ft_printf("\x1b[39m");
		}
		else if (map.c_map[i] == 3)
		{
			ft_printf("\x1b[33m");
			ft_printf("%02x", hex[i]);
			ft_printf("\x1b[39m");
		}
		else if (map.c_map[i] == 4)
		{
			ft_printf("\x1b[34m");
			ft_printf("%02x", hex[i]);
			ft_printf("\x1b[39m");
		}
		else if (map.c_map[i] == 0) {
			ft_printf("\x1b[39m");
			ft_printf("%02x", hex[i]);
		}
		i++;
		if (i % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
	printf("Cycles at : %li\n", map.t_cycles);
}
