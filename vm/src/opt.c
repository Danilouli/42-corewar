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

void	sortchamps(t_champ *champs, t_list **allprocess)
{
	t_champ	schamps[MAX_PLAYERS + 1];
	int i;
	int c;

	i = -1;
	c = 0;
	while (++i < MAX_PLAYERS)
		if (champs[i].name)
			schamps[c++] = champs[i];
	i = -1;
	ft_bzero(champs, sizeof(t_champ) * (MAX_PLAYERS + 1));
	while (++i < c) {
		ft_memcpy(&champs[i], &schamps[i], sizeof(t_champ));
		champs[i].num = i;
		ft_lstadd(allprocess, ft_lstlink(createproc(&champs[i], 0, NULL), sizeof(t_process)));
	}
	champs[i].name = NULL;
	champs[i].num = -1;
}

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
		else if (av[i][0] == '-' && ft_strlen(av[i]) >= 2 && ft_strchr(OPTION, av[i][1]))
		{
			ft_strpush(map->opt, av[i][1]);
			if (av[i][1] == 'd' && av[i + 1] && ft_isdigit(av[i + 1][0]))
				map->dump = ft_atoi(av[++i]);
			else if (av[i][1] == 'd' && ft_printf("The -d option must take a number you noob.\n"))
				return (NULL);
			else if (av[i][1] == 'm' && av[i][2] && ft_isdigit(av[i][2]))
			{
				if (ft_atoi(&av[i][2]) > 4 && ft_printf("Yeah sure, let's have 100 players whilst we're at it\n"))
					return (NULL);
				if (champs[ft_atoi(&av[i][2]) - 1].name
				&& ft_printf("Gave twice the same number for two different champions, are you retarded man ?\n"))
					return (NULL);
				else if (av[++i])
				{
					if (!(ischamp(av[i], &champs[ft_atoi(&av[i - 1][2]) - 1], ft_atoi(&av[i - 1][2]) - 1)
					&& ft_printf("NOT EVEN A CHAMPION DUDE WTF\n")))
						return (NULL);
					n_champ++;
				}
				else if (ft_printf("Not providing a champion, you man are a genius...\n"))
					return (NULL);
			}
			else if (av[i][1] == 'm' && ft_printf("Want some help reading the usage dude ?\n"))
				return (NULL);
		}
		else if (usage())
			return (NULL);
	}
	if (!n_champ && usage())
		return (NULL);
	sortchamps(champs, &allprocess);
	return (allprocess);
}
