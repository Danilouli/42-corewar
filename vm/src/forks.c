#include "corewar.h"

int	cfork(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_process	*tmp;
	short		k;
	short		*cast;

	(void)map;
	(void)champ;
	tmp = proccpy(&process);
	ft_memmove(&k, &map->map[(process->ptr + 1) % MEM_SIZE], 2);
	cast = &k;
	ft_short_endian_swap((unsigned short*)cast);
	tmp->ptr += (*cast % IDX_MOD);
	tmp->ptr %= MEM_SIZE;
	tmp->ptr = tmp->ptr >= MEM_SIZE ? tmp->ptr - MEM_SIZE : tmp->ptr;
	tmp->life--;
	ft_lstadd(allprocess, ft_lstlink(tmp, sizeof(t_process)));
	return (2);
}

int	lcfork(t_map *map, t_champ *champ, t_process *process, t_list **allprocess)
{
	t_process	*tmp;
	short		k;
	short		*cast;

	(void)map;
	(void)champ;
	if (!(tmp = proccpy(&process)))
		exit (1);
	ft_memmove(&k, &map->map[(process->ptr + 1) % MEM_SIZE], 2);
	cast = &k;
	ft_short_endian_swap((unsigned short*)cast);
	tmp->ptr += *cast;
	tmp->ptr %= MEM_SIZE;
	tmp->ptr = tmp->ptr >= MEM_SIZE ? tmp->ptr - MEM_SIZE : tmp->ptr;
	tmp->life--;
	ft_lstadd(allprocess, ft_lstlink(tmp, sizeof(t_process)));
	return (2);
}
