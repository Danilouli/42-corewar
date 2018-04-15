#ifndef COREWAR_H
# define COREWAR_H

#include "op.h"

# define OPTION "adsvbn"
# define NBOPT 6
# define STEALTH "--stealth"
# define LIFECODE 0xFFFFFFFF

typedef struct			s_champ
{
	char				num;
	char				*name;
	char				*comment;
	size_t				len_prog;
	char				*prog;
	uintmax_t			lastlife;
}						t_champ;

typedef struct			s_map
{
	unsigned char		*map;
	t_champ				**owner;
	uintmax_t			cycles;
}						t_map;

typedef struct			s_process
{
	unsigned char		*ptr;
	int					life;
	t_op				*op;
	unsigned char		*params;
	unsigned			cycles;
	t_champ				*champ;
	char				carry;
	char				*reg;
}						t_process;


int						ischamp(char *path, t_champ *champ, unsigned char n_champ);
t_process				*createproc(t_champ *champ, char carry, char *reg);
t_list					*option(int ac, char **av, char *opt, t_champ *champs);
size_t					champslen(t_champ *champs);
void					setmap(t_map *map, t_champ *champs, t_list *allprocess);

#endif
