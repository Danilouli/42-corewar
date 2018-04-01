/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaadia <dsaadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 19:18:47 by dsaadia           #+#    #+#             */
/*   Updated: 2018/04/01 20:42:15 by dsaadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/asm.h"

int	main(int ac, char **av)
{
	int		i;
	int		fd;
	char	*l;

	i = 1;
	if (ac <= 1)
	{
		ft_printf("Usage: ./asm [-a] <sourcefile.s>\n	-a : Instead of creating a \
		.cor file, outputs a stripped and annotated version of \
		the code to the standard output");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (1);
	while (get_next_line(fd, &l) == 1)
	{
		ft_putendl(l);
	}
	return (0);
}
