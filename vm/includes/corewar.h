#ifndef COREWAR_H
# define COREWAR_H

#include "op.h"

# define OPTION "adsvbn"
# define NBOPT 6
# define STEALTH "--stealth"

typedef struct	s_champ
{
	char		*name;
	char		*comment;
	t_list		*processus;
	size_t		len_prog;
	char		*prog;
}				t_champ;

typedef struct	s_map
{
	char		*map;
	t_champ		**owner;
}				t_map;

typedef struct	s_process
{
	t_map	*ptr;
	int		life;
	int		opcode;
	size_t	cycle;
}				t_process;


int	ischamp(char *path, t_champ *champ);
t_process		*createproc(int life);
t_champ			*option(int ac, char **av, char *opt, t_champ *champs);
size_t			champslen(t_champ *champs);
void			setmap(t_map *map, t_champ *champs);

#endif
