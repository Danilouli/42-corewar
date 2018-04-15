#include "corewar.h"

t_list	*option(int ac, char **av, char *opt, t_champ *champs)
{
	int				i;
	unsigned char	n_champ;
	t_list			*allprocess;

	i = 1;
	n_champ	= 0;
	allprocess = NULL;
	while (i < ac)
	{
		if (n_champ == 4)
		{
			ft_printf("Too many champions\n");
			return (NULL);
		}
		else if (!ft_strcmp(STEALTH, av[i]) && ft_strchr(opt, '-'))
			ft_strpush(opt, '-');
		else if (av[i][0] == '-' && ft_strlen(av[i]) == 2 && ft_strchr(OPTION, av[i][1]))
			ft_strpush(opt, av[i][1]);
		else if (ischamp(av[i], &champs[n_champ], n_champ))
		{
			ft_lstadd(&allprocess, ft_lstlink(createproc(&champs[n_champ], 1, NULL), sizeof(t_process)));
			ft_printf("max : %i\n", MAX_PLAYERS);
			n_champ++;
			ft_printf("OUT\n");
		}
		else
			return (NULL);
		i++;
	}
	champs[n_champ].name = NULL;
	return (allprocess);
}
