/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:18:41 by fsabatie          #+#    #+#             */
/*   Updated: 2018/04/17 22:55:45 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	usage(void)
{
	ft_putendl("Usage: ./corewar [-d -s | -b --stealth | -n --stealth] [-a] \
	<champion1.cor> <champion2.cor>");
	ft_putendl("	-a	: Prints the output from the \"aff\" instruction");
	ft_putendl("########################################## TEXT OUTPUT MODE");
	return (1);
}

int	main(int ac, char **av)
{
	char	opt[NBOPT];
	t_champ	champs[MAX_PLAYERS + 1];
	t_map	map;
	t_list	*allprocess;

	(void)av;
	if (ac < 2)
		return (usage());
	if (!(map.map = (unsigned char *)malloc(sizeof(char) * (MEM_SIZE + 1)))
		|| !(map.owner = (t_champ **)malloc(sizeof(t_champ *) * (MEM_SIZE + 1))))
		return (1);
	ft_bzero(opt, ft_strlen(OPTION));
	ft_bzero(map.map, MEM_SIZE);
	ft_bzero(map.owner, MEM_SIZE * sizeof(t_champ *));
	if (!(allprocess = option(ac, av, opt, champs)))
		return (1);
	ft_printf("OPT : %s\n", opt);
	setmap(&map, champs, allprocess);
	prt_map_hex(map);
	process_operations(&map, champs, &allprocess);
}
