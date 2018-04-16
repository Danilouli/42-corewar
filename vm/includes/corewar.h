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
	intmax_t			lastlife;
}						t_champ;

typedef struct			s_map
{
	unsigned char		*map;
	t_champ				**owner;
	uintmax_t			cycles;
}						t_map;

typedef struct			s_process
{
	unsigned			ptr;
	t_bool				active;
	int					life;
	char				op;
	unsigned char		*params;
	unsigned			cycles;
	t_champ				*champ;
	char				carry;
	char				*reg;
}						t_process;

typedef struct			s_arg
{
	unsigned char		type;
	unsigned char		arg[4];
}						t_arg;

t_list					*option(int ac, char **av, char *opt, t_champ *champs);
void					setmap(t_map *map, t_champ *champs, t_list *allprocess);

/*
Process functions
*/
t_process				*createproc(t_champ *champ, char carry, char *reg);
void					delprocess(void *content, size_t content_size);
void					process_operations(t_map *map, t_champ *champs, t_list **allprocess);
int						proc_isalive(t_list *list, void *ref);

/*
Champions functions
*/
size_t					champslen(t_champ *champs);
int						ischamp(char *path, t_champ *champ, unsigned char n_champ);
int						champ_isalive(intmax_t cycles, t_list *list, t_champ *champs);

#endif
