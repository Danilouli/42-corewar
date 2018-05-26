/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlay <vlay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 23:25:55 by vlay              #+#    #+#             */
/*   Updated: 2018/05/20 16:25:12 by vlay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


// TODO: S'assurer que l'affichage en ncurses ou OpenGL soit prioritaire sur les autres modes.

t_list	*option(int ac, char **av, t_map *map, t_champ *champs)
{
	int				i;
	unsigned char	n_champ;
	t_list			*allprocess;

	i = 0;
	n_champ	= 0;
	allprocess = NULL;
	while (++i < ac)
	{
		if ((n_champ == MAX_PLAYERS) && (ft_printf("Too many champions.\n"))) // Straight forward
			return (NULL);
		else if (!ft_strcmp(STEALTH, av[i]) && !ft_strchr(map->opt, '-')) // Adds '-' to opt if stealth is activated
			ft_strpush(map->opt, '-');
		else if (av[i][0] == '-' && ft_strlen(av[i]) == 2 && ft_strchr(OPTION, av[i][1]))
		{
			ft_strpush(map->opt, av[i][1]);
			if (av[i][1] == 'd' && ft_isdigit(av[++i][0]))
				map->dump = ft_atoi(av[i]);
			else if (av[i - 1][1] == 'd' && ft_printf("The -d option must take a number you noob.\n"))
				return (NULL);
		}
		else if (ischamp(av[i], &champs[n_champ], n_champ))
			ft_lstadd(&allprocess, ft_lstlink(createproc(&champs[n_champ++], 0, NULL), sizeof(t_process)));
		else
			return (NULL);
	}
	if (!n_champ && usage())
		return (NULL);
	champs[n_champ].name = NULL;
	champs[n_champ].num = -1;
	return (allprocess);
}
