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
	ft_putendl("#### Text output mode #######################################################");
	ft_putendl("	-a	: Prints the output from the \"aff\" instruction");
	ft_putendl("#### Binary output mode #####################################################");
	ft_putendl("	-b  : Binary output mode for corewar");
	ft_putendl("	--stealth : Hides the real contents of the memory");
	ft_putendl("#### OpenGL output mode #####################################################");
	ft_putendl("	-n        : OpenGL output mode");
	ft_putendl("	--stealth : Hides the real contents of the memory");
	return (1);
}

int	main(int ac, char **av)
{
	char	opt[NBOPT];
	t_champ	champs[MAX_PLAYERS + 1];
	t_map	map;
	t_list	*allprocess;
	t_render r;

	if (ac < 2)
		return (usage());
	if (!(map.map = (unsigned char *)malloc(sizeof(char) * (MEM_SIZE + 1)))
	|| !(map.c_map = (unsigned char *)malloc(sizeof(char) * (MEM_SIZE + 1)))
	|| !(map.p_map = (unsigned char *)malloc(sizeof(char) * (MEM_SIZE + 1))))
		return (1);
	ft_bzero(&r, sizeof(t_render));
	ft_bzero(opt, ft_strlen(OPTION));
	ft_bzero(map.map, MEM_SIZE);
	ft_bzero(map.c_map, MEM_SIZE);
	ft_bzero(map.p_map, MEM_SIZE);
	if (!(allprocess = option(ac, av, opt, champs)))
		return (1);
	if (ft_strchr(opt, 'n'))
		init_context(&r, &map); // Make sure this doesn't segfault
	setmap(&map, champs, allprocess);
	prt_map_hex(map);
	process_operations(&r, &map, champs, &allprocess);
}
