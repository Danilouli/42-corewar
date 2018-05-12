#include "corewar.h"

t_process	*proccpy(t_process **process)
{
	t_process	*res;

	if (!(res = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	ft_memcpy(res, *process, sizeof(t_process));
	res->active = 0;
	if (!(res->reg = ft_memdup((*process)->reg, REG_NUMBER * REG_SIZE)))
		return (NULL);
	return (res);
}

t_process	*createproc(t_champ *champ, char carry, char *reg)
{
	t_process	*proc;
	unsigned	*cast;

	if (!(proc = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	proc->ptr = 0;
	proc->life = CYCLE_TO_DIE;
	proc->champ = champ;
	proc->op = 0;
	proc->cycles = 0;
	proc->carry = carry;
	proc->active = 0;
	if (reg)
		proc->reg = ft_memdup(reg, REG_NUMBER * REG_SIZE);
	else
	{
		proc->reg = (unsigned char*)ft_strnew(REG_NUMBER * REG_SIZE);
		cast = (unsigned *)proc->reg;
		*cast = LIFECODE - champ->num;
		ft_endian_swap(cast);
	}
	return (proc);
}

void	delprocess(void *content, size_t content_size)
{
	t_process	*process;

	(void)content_size;
	process = (t_process *)content;
	if (process)
		if (process->reg) {
			free(process->reg);
			free(process);
		}
}

t_list	*proc_filter(t_list *list, unsigned char *pmap)
{
	t_list		*result;
	t_list		*next;
	t_process	*proc;

	result = NULL;
	while (list)
	{
		proc = (t_process *)list->content;
		next = list->next;
		if (proc->life > 0)
		{
			list->next = NULL;
			proc->life = 0;
			ft_lstappend(&result, list);
		}
		else if (!(pmap[proc->ptr] = 0))
		{
			delprocess(list->content, list->content_size);
			free(list);
		}
		list = next;
	}
	return (result);
}
