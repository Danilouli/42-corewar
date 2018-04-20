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
		ft_printf("%02x", hex[i]);
		i++;
		if (i % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}
