/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:18:41 by fsabatie          #+#    #+#             */
/*   Updated: 2018/03/21 20:58:00 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
		ft_printf("Usage: ./asm [-a] <sourcefile.s>\n	-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output");
	else
	{
		while (i < argc)
		{
			if (*argv[i] == '-')
			i++;
		}
	}
	return (0);
}
