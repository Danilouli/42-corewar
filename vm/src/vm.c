/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:18:41 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/10 17:32:28 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void bz(t_render *r, char *opt, t_map *map)
{
	ft_bzero(r, sizeof(t_render));
	ft_bzero(opt, ft_strlen(OPTION));
	ft_bzero(map->map, MEM_SIZE);
	ft_bzero(map->c_map, MEM_SIZE);
	ft_bzero(map->p_map, MEM_SIZE);
}

int	usage(void)
{
	ft_putendl("Usage: ./corewar [ -d -s | -n --stealth | -o | -a ] \
	<champion1.cor> <champion2.cor> ...");
	ft_putendl("#### Text output mode #######################################################");
	ft_putendl("	-a	: Prints the output from the \"aff\" instruction");
	ft_putendl("#### Graphical output mode ##################################################");
	ft_putendl("	-o        : OpenGL output mode");
	ft_putendl("	-n        : Ncurses output mode");
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
	bz(&r, &opt[0], &map);
	if (!(allprocess = option(ac, av, opt, champs)))
		return (1);
	if ((r.skip = 1) && ft_strchr(opt, 'o'))
		init_context(&r, &map); // Make sure this doesn't segfault
	if (ft_strchr(opt, 'n') && !(ft_strchr(opt, 'o')))
		r.ncurses = 1; // Make sure this doesn't segfault
	setmap(&map, champs, allprocess);
	map.cycles = CYCLE_TO_DIE;
	process_operations(&r, &map, champs, &allprocess);
	if (r.ncurses)
		endwin();
	prt_map_hex(map);
	ft_printf("Contestant %i, \"%s\", has won\n", whowins(champs)->num + 1, whowins(champs)->name);
	freechamp(champs);
}
