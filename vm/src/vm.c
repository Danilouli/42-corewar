/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:18:41 by fsabatie          #+#    #+#             */
/*   Updated: 2018/05/12 19:08:39 by vlay             ###   ########.fr       */
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
	ft_putendl("Usage: ./corewar [ -d [-n | -o | -a ]] \
	-m(a number) <champion1.cor> -m(another one) <champion2.cor> ...");
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
	ft_bzero((t_champ*)&champs[0], sizeof(t_champ) * MAX_PLAYERS + 1);
	map.opt = &opt[0];
	if (!(allprocess = option(ac, av, &map, champs)))
		return (1);
	if ((r.skip = 1) && ft_strchr(opt, 'o'))
		init_context(&r, &map);
	if (ft_strchr(opt, 'n') && !(ft_strchr(opt, 'o')))
		r.ncurses = 1;
	setmap(&map, champs, allprocess);
	map.cycles = CTD;
	process_operations(&r, &map, champs, &allprocess);
	if (r.ncurses)
		endwin();
	ft_bzero(map.p_map, MEM_SIZE);
	prt_map_hex(map);
	!ft_strchr(opt, 'd') ? ft_printf("Contestant %i, \"%s\", has won\n", \
	whowins(champs)->num + 1, whowins(champs)->name) : (void)opt;
	freechampmap(champs, &map);
}
